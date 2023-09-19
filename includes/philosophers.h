/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:11:52 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/19 21:11:15 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include "../libft/libft.h"

struct	s_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				nb_eat;
	size_t			last_time_ate;
	bool			is_dead;
	struct s_data	*data;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
}		t_philo;

typedef struct s_data
{
	int								nb_philo;
	int								time_to_die;
	int								time_to_eat;
	int								time_to_sleep;
	int								nb_eat_max;
	size_t							start_time;
	t_philo							**philo;
	pthread_mutex_t					*forks;
	pthread_mutex_t					end;
	pthread_mutex_t					write;
	pthread_mutex_t					nb_eat;
}			t_data;

//srcs/main.c
int		main(int argc, char **argv);

//srcs/init.c
int		init(t_data *data, int argc, char **argv);

//srcs/free.c
void	free_mutex(t_data *data, int i, int failed_fork);

//srcs/routine.c
void	*routine(void *pointer_to_philo);

//srcs/utils.c
size_t	gettime(void);
int		print(t_philo *philo, int code);




#endif