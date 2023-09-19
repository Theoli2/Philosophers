/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:55:26 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/19 21:42:40 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

size_t	gettime(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (-1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	print2(t_philo *philo, int code)
{
	if (code == 2)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%zu %d is sleeping\n", \
		gettime() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->write);
	}
	if (code == 3)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%zu %d is thinking\n", \
		gettime() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->write);
	}
	if (code == 4)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%zu %d died\n", \
		gettime() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->write);
	}
	if (code > 4)
		return (1);
	return (0);
}

int	print(t_philo *philo, int code)
{
	int	i;

	if (code == 0)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%zu %d has taken a fork\n", \
		gettime() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->write);
	}
	if (code == 1)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%zu %d is eating\n", \
		gettime() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->write);
	}
	if (code > 1)
	{
		i = print2(philo, code);
		return (i);
	}
	return (0);
}
