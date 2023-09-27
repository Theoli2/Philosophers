/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:03:10 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/27 08:52:29 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_data(t_data *data, int argc, char **argv)
{
	if (ft_atoi_bool(argv[1], &data->nb_philo) == false)
		return (printf("invalid amount of philosophers\n"), 1);
	if (ft_atoi_bool(argv[2], &data->time_to_die) == false)
		return (printf("invalid time to die\n"), 1);
	if (ft_atoi_bool(argv[3], &data->time_to_eat) == false)
		return (printf("invalid time to eat\n"), 1);
	if (ft_atoi_bool(argv[4], &data->time_to_sleep) == false)
		return (printf("invalid time to sleep\n"), 1);
	data->is_dead = false;
	data->all_ate = false;
	if (argc == 6)
	{
		if (ft_atoi_bool(argv[5], &data->nb_eat_max) == false)
			return (printf("invalid amount of times to eat\n"), 1);
	}
	else
		data->nb_eat_max = -1;
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->end, NULL))
		return (1);
	if (pthread_mutex_init(&data->write, NULL))
		return (pthread_mutex_destroy(&data->end), 1);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (free_mutex(data, 2, i), 1);
		i++;
	}
	return (0);
}

int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].nb_eat = 0;
		data->philo[i].last_time_ate = gettime();
		data->philo[i].data = data;
		if (!(i & 1))
		{
			data->philo[i].fork1 = &data->forks[(i + 1) % data->nb_philo];
			data->philo[i].fork2 = &data->forks[i];
		}
		else
		{
			data->philo[i].fork1 = &data->forks[i];
			data->philo[i].fork2 = &data->forks[(i + 1) % data->nb_philo];
		}
		i++;
	}
	return (0);
}

int	init(t_data *data, int ac, char **av)
{
	if (init_data(data, ac, av))
		return (1);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!(data->philo))
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!(data->forks))
		return (free(data->philo), 1);
	if (init_mutex(data))
		return (free(data->philo), free(data->forks), 1);
	if (init_philo(data))
		return (free(data->philo), free(data->forks), 1);
	return (0);
}
