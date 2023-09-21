/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:21:40 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/21 02:28:39 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	thread_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i]->thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		*data;
	int			i;
	int			j;
	int			k;

	data = malloc(sizeof(t_data));
	if (argc != 5 && argc != 6)
		return (write (1, "invalid amount of parameters\n", 29), 1);
	init(data, argc, argv);
	i = 0;
	data->start_time = gettime();
	if ((int)data->start_time == -1)
		return (1);
	while (i < data->nb_philo)
	{
		pthread_create(&data->philo[i]->thread, NULL, &routine, data->philo[i]);
		i++;
	}
	j = 0;
	k = 0;
	while (1)
	{
		while (j < data->nb_philo)
		{
			pthread_mutex_lock(&data->end);
			pthread_mutex_lock(&data->last_time_ate);
			if ((size_t)data->time_to_die < gettime() - data->philo[j]->last_time_ate)
			{
				pthread_mutex_unlock(&data->last_time_ate);
				data->is_dead = true;
				pthread_mutex_lock(&data->write);
				printf("%zu %d is dead\n temp : %ld",  
				gettime() - data->start_time, j + 1, gettime() - data->philo[j]->last_time_ate);
				pthread_mutex_unlock(&data->write);
				pthread_mutex_unlock(&data->end);
				return (thread_join(data), 0);
			}
			pthread_mutex_unlock(&data->last_time_ate);
			pthread_mutex_unlock(&data->end);
			pthread_mutex_lock(&data->philo[j]->data->nb_eat);
			if (data->philo[j]->nb_eat >= \
			data->nb_eat_max && data->nb_eat_max != -1)
				k++;
			pthread_mutex_unlock(&data->philo[j]->data->nb_eat);
			j++;
		}
		if (k == data->nb_philo)
		{
			pthread_mutex_lock(&data->nb_eat);
			data->all_ate = true;
			pthread_mutex_unlock(&data->nb_eat);
			return (thread_join(data), 0);
		}
		j = 0;
	}
	return (0);
}
