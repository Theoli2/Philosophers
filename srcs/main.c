/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:21:40 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/14 00:12:22 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *arg)
{
	
	// Arrêt propre du thread
	pthread_exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;

	if (argc != 5 || argc != 6)
		return (write (1, "invalid amount of parameters\n", 29), 1);
	init(&data, argc, argv);
	i = 0;
	
	while (i < data.nb_philo)
	{
		pthread_create(data.nb_philo[i], NULL, routine, NULL);
		i++;
	}
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_join(data.nb_philo[i], NULL);
		i++;
	}
	return (0);
}
