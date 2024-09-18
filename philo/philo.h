/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:51:08 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/18 12:57:20 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0
# define PHILO_MAX 200

typedef struct s_ph
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				count;
	int				ate;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	long			dine_count;
	size_t			start_time;
	size_t			last_meal;
	int				*dead_flag;
	int				*error_flag;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*error_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
}	t_ph;

typedef struct s_table
{
	int				dead_flag;
	int				error_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	error_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	t_ph			*philo;
}	t_table;

int		check_input(int argc, char **argv);
int		ft_atoi(const char *nptr);
int		init(t_table *table, t_ph *philo, pthread_mutex_t *fork, char **argv);
void	destroy_mutex(t_table *table, pthread_mutex_t *fork, int count);
int		dinner(t_table *table, pthread_mutex_t	*fork);
void	*monitor(void *ptr);
void	*routine(void *ptr);
size_t	get_current_time(t_ph *philo);
int		ft_usleep(size_t ms, t_ph *philo);
int		check_dead(t_ph *philo);
void	print_status(int id, char *str, t_ph *philo);
void	set_order(pthread_mutex_t **f_fork, pthread_mutex_t **s_fork, t_ph *ph);

#endif
