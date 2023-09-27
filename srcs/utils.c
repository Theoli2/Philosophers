/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:55:26 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/27 01:45:31 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	thread_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

int	ft_usleep(t_philo	*philo, size_t time)
{
	size_t const	target = gettime() + time;

	while (gettime() < target)
	{
		pthread_mutex_lock(&philo->data->end);
		if (philo->data->is_dead == true || philo->data->all_ate == true)
			return (pthread_mutex_unlock(&philo->data->end), 1);
		pthread_mutex_unlock(&philo->data->end);
		usleep(100);
	}
	return (0);
}

size_t	gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->end);
	pthread_mutex_lock(&philo->data->write);
	if (philo->data->is_dead == true || philo->data->all_ate == true)
	{
		pthread_mutex_unlock(&philo->data->write);
		pthread_mutex_unlock(&philo->data->end);
		return (1);
	}
	printf("%zu %d %s",
		gettime() - philo->data->start_time, philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
	pthread_mutex_unlock(&philo->data->end);
	return (0);
}

void	ft_free(t_data *data)
{
	free(data->philo);
	free(data->forks);
}
