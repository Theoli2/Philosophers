/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:35:42 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/22 18:44:51 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	eat2(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->last_time_ate);
	philo->last_time_ate = gettime();
	pthread_mutex_unlock(&philo->data->last_time_ate);
	if (ft_usleep(philo, philo->data->time_to_eat))
	{
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		return (1);
	}
	pthread_mutex_lock(&philo->data->end);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->data->end);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	return (0);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	if (print(philo, "has taken a fork\n"))
	{
		pthread_mutex_unlock(philo->fork1);
		return (1);
	}
	// pthread_mutex_lock(&philo->data->write);
	// printf("%i %li\n", philo->id, (size_t)*philo->fork1);
	// pthread_mutex_unlock(&philo->data->write);
	pthread_mutex_lock(philo->fork2);
	if (print(philo, "has taken a fork\n"))
	{
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		return (1);
	}
	// pthread_mutex_lock(&philo->data->write);
	// printf("%i %li\n", philo->id, (size_t)*philo->fork2);
	// pthread_mutex_unlock(&philo->data->write);
	if (print(philo, "is eating\n"))
	{
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		return (1);
	}
	if (eat2(philo))
		return (1);
	return (0);
}
