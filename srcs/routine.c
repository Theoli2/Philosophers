/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:59:52 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/21 02:30:08 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		return (1);
	}
	if (print(philo, "is eating\n"))
	{
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		return (1);
	}
	pthread_mutex_lock(&philo->data->last_time_ate);
	philo->last_time_ate = gettime();
	pthread_mutex_unlock(&philo->data->last_time_ate);
	if (ft_usleep(philo, philo->data->time_to_eat))
	{
		pthread_mutex_unlock(philo->fork1);
		pthread_mutex_unlock(philo->fork2);
		return (1);
	}
	pthread_mutex_lock(&philo->data->nb_eat);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->data->nb_eat);
	pthread_mutex_unlock(philo->fork1);
	pthread_mutex_unlock(philo->fork2);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (print(philo, "is sleeping\n"))
		return (1);
	if (ft_usleep(philo, philo->data->time_to_sleep))
		return (1);
	if (print(philo, "is thinking\n"))
		return (1);
	return (0);
}

void	*routine(void *pointer_to_philo)
{
	t_philo	*philo;

	philo = (t_philo *)pointer_to_philo;
	pthread_mutex_lock(&philo->data->last_time_ate);
	philo->last_time_ate = gettime();
	pthread_mutex_unlock(&philo->data->last_time_ate);
	if (philo->data->nb_philo == 1)
	{
		while (1)
		{
			pthread_mutex_lock(&philo->data->end);
			if (philo->last_time_ate + philo->data->time_to_die < gettime())
			{
				philo->data->is_dead = true;
				pthread_mutex_unlock(&philo->data->end);
				break ;
			}
			pthread_mutex_unlock(&philo->data->end);
		}
		pthread_exit(EXIT_SUCCESS);
	}
	if (philo->data->nb_philo % 2 == 1 && philo->id == 1)
	{
		// pthread_mutex_lock(&philo->data->write);
		// printf("%i\n", philo->id);
		// pthread_mutex_unlock(&philo->data->write);
		ft_usleep(philo, philo->data->time_to_eat / philo->data->nb_philo);
	}
	while (1)
	{
		if (eat(philo))
			pthread_exit(EXIT_SUCCESS);
		if (ft_sleep(philo))
			pthread_exit(EXIT_SUCCESS);
	}
	pthread_exit(EXIT_SUCCESS);
}
