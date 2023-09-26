/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:21:40 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/26 23:16:26 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_error(t_data *data, int i)
{
	while (i >= 0)
	{
		pthread_join(data->philo[i].thread, NULL);
		i--;
	}
	ft_free(data);
}

int	main(int argc, char **argv)
{
	t_data		data;
	int			i;

	if (argc != 5 && argc != 6)
		return (printf ("invalid amount of parameters\n"), 1);
	if (init(&data, argc, argv))
		return (1);
	i = 0;
	data.start_time = gettime();
	while (i < data.nb_philo)
	{
		if (pthread_create(&data.philo[i].thread, \
		NULL, &routine, &data.philo[i]))
			return (ft_error(&data, i), 1);
		i++;
	}
	while (1)
	{
		if (monitoring(&data))
			break ;
		usleep(100);
	}
	ft_free(&data);
	return (0);
}
