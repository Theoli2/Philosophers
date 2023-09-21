/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:55:26 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/21 01:49:34 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_usleep(t_philo	*philo, size_t time)
{
	size_t	start;

	start = gettime();
	while (gettime() - start < time)
	{
		pthread_mutex_lock(&philo->data->end);
		pthread_mutex_lock(&philo->data->nb_eat);
		if (philo->data->is_dead == true || philo->data->all_ate == true)
		{
			pthread_mutex_unlock(&philo->data->end);
			pthread_mutex_unlock(&philo->data->nb_eat);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->end);
		pthread_mutex_unlock(&philo->data->nb_eat);
		usleep(100);
	}
	return (0);
}

size_t	gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->end);
	pthread_mutex_lock(&philo->data->nb_eat);
	if (philo->data->is_dead == true || philo->data->all_ate == true)
	{
		pthread_mutex_unlock(&philo->data->end);
		pthread_mutex_unlock(&philo->data->nb_eat);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->end);
	pthread_mutex_unlock(&philo->data->nb_eat);
	pthread_mutex_lock(&philo->data->write);
	printf("%zu philo last time ate : %li %d %s", \
	gettime() - philo->data->start_time, philo->last_time_ate - philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
	return (0);
}
