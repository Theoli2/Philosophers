/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:58:09 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/19 18:08:19 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	free_mutex(t_data *data, int i, int failed_fork)
{
	int	j;

	j = 0;
	if (i == 2)
	{
		pthread_mutex_destroy(&data->end);
		pthread_mutex_destroy(&data->write);
		while (j < failed_fork)
		{
			pthread_mutex_destroy(&data->forks[j]);
			j++;
		}
	}
}
