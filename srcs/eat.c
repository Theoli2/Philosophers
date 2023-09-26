/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 17:35:42 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/23 07:06:56 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	eat2(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->end);
	philo->last_time_ate = gettime();
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->data->end);
	if (ft_usleep(philo, philo->data->time_to_eat))
	{
		pthread_mutex_unlock(philo->fork2);
		pthread_mutex_unlock(philo->fork1);
		return (1);
	}
	pthread_mutex_unlock(philo->fork2);
	pthread_mutex_unlock(philo->fork1);
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
	pthread_mutex_lock(philo->fork2);
	if (print(philo, "has taken a fork\n"))
	{
		pthread_mutex_unlock(philo->fork2);
		pthread_mutex_unlock(philo->fork1);
		return (1);
	}
	if (print(philo, "is eating\n"))
	{
		pthread_mutex_unlock(philo->fork2);
		pthread_mutex_unlock(philo->fork1);
		return (1);
	}
	if (eat2(philo))
		return (1);
	return (0);
}
