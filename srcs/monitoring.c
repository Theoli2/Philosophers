/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:27:56 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/23 10:41:40 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	monitoring_2(t_data *data, int i, int j)
{
	if (data->nb_eat_max != -1 && data->philo[i].nb_eat >= data->nb_eat_max)
		j++;
	if (gettime() - data->philo[i].last_time_ate > (size_t)data->time_to_die)
	{
		data->is_dead = true;
		pthread_mutex_lock(&data->write);
		printf("%zu %i died\n", gettime() - data->start_time,
			data->philo[i].id);
		pthread_mutex_unlock(&data->write);
		return (-1);
	}
	return (j);
}

int	monitoring(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_lock(&data->end);
		j = monitoring_2(data, i, j);
		if (j == -1)
			return (pthread_mutex_unlock(&data->end), thread_join(data), 1);
		pthread_mutex_unlock(&data->end);
		i++;
	}
	pthread_mutex_lock(&data->end);
	if (j == data->nb_philo)
	{
		data->all_ate = true;
		pthread_mutex_unlock(&data->end);
		return (thread_join(data), 1);
	}
	pthread_mutex_unlock(&data->end);
	return (0);
}
