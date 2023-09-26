/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:59:52 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/23 10:11:26 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_sleep(t_philo *philo)
{
	if (print(philo, "is sleeping\n"))
		return (1);
	if (ft_usleep(philo, philo->data->time_to_sleep))
		return (1);
	if (print(philo, "is thinking\n"))
		return (1);
	ft_usleep(philo, (philo->data->time_to_die - (philo->data->time_to_sleep
				+ philo->data->time_to_eat)) * 0.5);
	return (0);
}

int	routine_one(t_philo *philo)
{		
	pthread_mutex_lock(philo->fork1);
	if (print(philo, "has taken a fork\n"))
	{
		pthread_mutex_unlock(philo->fork1);
		return (1);
	}
	pthread_mutex_unlock(philo->fork1);
	while (1)
	{
		pthread_mutex_lock(&philo->data->end);
		if (philo->data->is_dead == true || philo->data->all_ate == true)
		{
			pthread_mutex_unlock(&philo->data->end);
			break ;
		}
		pthread_mutex_unlock(&philo->data->end);
	}
	return (1);
}

void	*routine(void *pointer_to_philo)
{
	t_philo	*philo;

	philo = (t_philo *)pointer_to_philo;
	if (philo->data->nb_philo == 1)
	{
		routine_one(philo);
		return (NULL);
	}
	if (philo->id % 2 == 1 && philo->data->nb_philo % 2 == 0)
	{
		ft_usleep(philo, philo->data->time_to_eat);
	}
	if (philo->data->nb_philo % 2 == 1 && philo->id - 1 == 1)
	{
		ft_usleep(philo, philo->data->time_to_eat);
	}
	while (!eat(philo) && !ft_sleep(philo))
		;
	return (NULL);
}
