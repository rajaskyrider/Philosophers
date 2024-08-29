/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:51:08 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/29 16:07:47 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>

# define TRUE 1
# define FALSE 0
# define PHILO_MAX 200

typedef struct s_ph
{
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
	int				dead_flag;
	int				error_flag;
	sem_t			*write_lock;
	sem_t			*forks;
	sem_t			*dine_lock;
}	t_ph;


int		check_input(int argc, char **argv);
int		ft_atoi(const char *nptr);
int		init(t_ph *philo, pthread_mutex_t *fork, char **argv);
int		dinner(t_ph *philo, int count);
int		routine(t_ph *philo);
size_t	get_current_time(t_ph *philo);
int		ft_usleep(size_t ms, t_ph *philo);
int		check_dead(t_ph *philo);
void	print_status(int id, char *str, t_ph *philo);

#endif
