/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:59:52 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/19 20:13:17 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *pointer_to_philo)
{
	t_philo	*philo;

	philo = (t_philo *)pointer_to_philo;
	(void)philo;
	// pthread_mutex_lock(&philo->data->start);
	// printf("philo %d\n", philo->id);
	pthread_exit(EXIT_SUCCESS);
}
