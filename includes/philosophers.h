/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlivroze <tlivroze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:11:52 by tlivroze          #+#    #+#             */
/*   Updated: 2023/09/26 23:17:09 by tlivroze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				nb_eat;
	size_t			last_time_ate;
	struct s_data	*data;
	pthread_mutex_t	*fork1;
	pthread_mutex_t	*fork2;
}		t_philo;

typedef struct s_data
{
	int					nb_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_eat_max;
	bool				is_dead;
	bool				all_ate;
	size_t				start_time;
	t_philo				*philo;
	pthread_mutex_t		*forks;
	pthread_mutex_t		end;
	pthread_mutex_t		write;
}			t_data;

//srcs/main.c
int		main(int argc, char **argv);

//srcs/init.c
int		init(t_data *data, int argc, char **argv);

//srcs/free.c
void	free_mutex(t_data *data, int i, int failed_fork);

//srcs/routine.c
void	*routine(void *pointer_to_philo);

//srcs/monitoring.c
int		monitoring(t_data *data);

//srcs/utils.c
size_t	gettime(void);
int		print(t_philo *philo, char *str);
int		ft_usleep(t_philo	*philo, size_t time);
void	thread_join(t_data *data);
void	ft_free(t_data *data);

//srcs/eat.c
int		eat(t_philo *philo);

//srcs/ft_atoi_bool.c
bool	ft_atoi_bool(char *str, int	*nb);

//srcs/itoa.c
char	*ft_itoa(int n);

//srcs/atoi.c
int		ft_atoi(const char *nptr);

//srcs/ft_strncmp.c
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//srcs/ft_strlen.c
size_t	ft_strlen(const char *s);

#endif