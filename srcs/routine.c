/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:59:52 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/19 21:48:53 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork1);
	print(philo, 0);
	pthread_mutex_lock(philo->fork2);
	print(philo, 0);
	philo->last_time_ate = gettime();
	pthread_mutex_lock(&philo->data->nb_eat);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->data->nb_eat);
	print(philo, 1);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	// return (0);
}

void	ft_sleep(t_philo *philo)
{
	print(philo, 2);
	usleep(philo->data->time_to_sleep * 1000);
	print(philo, 3);
}

void	*routine(void *pointer_to_philo)
{
	t_philo	*philo;

	philo = (t_philo *)pointer_to_philo;
	philo->last_time_ate = gettime();
	if (philo->data->nb_philo == 1)
	{
		while (1)
		{
			pthread_mutex_lock(&philo->data->end);
			if (philo->last_time_ate + philo->data->time_to_die < gettime())
			{
				philo->is_dead = true;
				pthread_mutex_unlock(&philo->data->end);
				break ;
			}
			pthread_mutex_unlock(&philo->data->end);
		}
		pthread_exit(EXIT_SUCCESS);
	}
	if (philo->id % 2 == 0 && philo->id == 1)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->nb_eat);
		if (philo->data->nb_eat_max != -1 \
		&& philo->nb_eat >= philo->data->nb_eat_max)
		{	
			pthread_mutex_unlock(&philo->data->nb_eat);
			break ;
		}	
		pthread_mutex_unlock(&philo->data->nb_eat);
		eat(philo);
		ft_sleep(philo);
		pthread_mutex_lock(&philo->data->end);
		if (philo->last_time_ate + philo->data->time_to_die < gettime())
		{
			philo->is_dead = true;
			pthread_mutex_unlock(&philo->data->end);
		}
		pthread_mutex_unlock(&philo->data->end);
	}
	pthread_exit(EXIT_SUCCESS);
}
