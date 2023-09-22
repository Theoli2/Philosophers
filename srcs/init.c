/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 00:03:10 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/22 19:03:57 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//SECURISER LES ATOI !!!!!!!
void	init_data(t_data *data, int argc, char **argv)
{
	data->nb_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->is_dead = false;
	data->all_ate = false;
	if (argc == 6)
		data->nb_eat_max = ft_atoi(argv[5]);
	else
		data->nb_eat_max = -1;
}

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->end, NULL))
		return (1);
	if (pthread_mutex_init(&data->write, NULL))
		return (free(&data->end), 1);
	if (pthread_mutex_init(&data->last_time_ate, NULL))
		return (free(&data->end), free(&data->write), 1);
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
		data->philo[i] = malloc(sizeof(t_philo));
		if (!data->philo[i])
			return (free_mutex(data, 2, i), 1);
		data->philo[i]->id = i + 1;
		data->philo[i]->nb_eat = 0;
		data->philo[i]->last_time_ate = 0;
		data->philo[i]->data = data;
		if (i % 2 == 0)
		{
			data->philo[i]->fork1 = &data->forks[(i + 1) % data->nb_philo];
			data->philo[i]->fork2 = &data->forks[i];
		}
		else
		{
			data->philo[i]->fork1 = &data->forks[i];
			data->philo[i]->fork2 = &data->forks[(i + 1) % data->nb_philo];
		}
		i++;
	}
	return (0);
}

int	init(t_data *data, int ac, char **av)
{
	init_data(data, ac, av);
	data->philo = malloc(sizeof(t_philo *) * data->nb_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (init_mutex(data))
		return (free(data->philo), free(data->forks), 1);
	if (init_philo(data))
		return (free(data->philo), free(data->forks), 1);
	return (0);
}
