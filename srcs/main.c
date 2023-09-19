/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:21:40 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/19 21:45:44 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_data		*data;
	int			i;
	int			j;

	data = malloc(sizeof(t_data));
	if (argc != 5 && argc != 6)
		return (write (1, "invalid amount of parameters\n", 29), 1);
	init(data, argc, argv);
	i = 0;
	data->start_time = gettime();
	if ((int)data->start_time == -1)
		return (1);
	while (i < data->nb_philo)
	{
		pthread_create(&data->philo[i]->thread, NULL, &routine, data->philo[i]);
		i++;
	}
	j = 0;
	while (1)
	{
		while (j < data->nb_philo)
		{
			pthread_mutex_lock(&data->end);
			pthread_mutex_lock(&data->philo[j]->data->nb_eat);
			if (data->philo[j]->is_dead == true || \
			data->philo[j]->nb_eat == data->nb_eat_max)
			{
				pthread_mutex_unlock(&data->philo[j]->data->nb_eat);
				pthread_mutex_unlock(&data->end);
				if (data->philo[j]->is_dead == true)
					print(data->philo[j], 4);
				j = -2;
				break ;
			}
			pthread_mutex_unlock(&data->philo[j]->data->nb_eat);
			pthread_mutex_unlock(&data->end);
			j++;
		}
		if (j >= 0)
			j = 0;
		else
			break ;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(data->philo[i]->thread, NULL);
		i++;
	}
	printf("end\n");
	return (0);
}
