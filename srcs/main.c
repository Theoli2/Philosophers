/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:21:40 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/22 18:45:50 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_data		*data;
	int			i;

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
	while (1)
	{
		if (monitoring(data))
			return (0);
	}
	return (0);
}
