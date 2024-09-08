/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:51:08 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/09 01:44:36 by rpandipe         ###   ########.fr       */
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
# include <signal.h>
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
	int				error_flag;
	sem_t			*waiter1;
	sem_t			*waiter2;
	sem_t			*forks;
	sem_t			*write_lock;
	sem_t			*dine_lock;
	sem_t			*dead_lock;
	sem_t			*flag_lock;
	int				must_die;
}	t_ph;

int		check_input(int argc, char **argv);
int		ft_atoi(const char *nptr);
int		dinner(t_ph *philo);
void	*routine(void *ptr);
size_t	get_current_time(t_ph *philo);
int		ft_usleep(size_t ms, t_ph *philo);
int		check_dead(t_ph *philo);
void	print_status(int id, char *str, t_ph *philo);
void	ft_sem_close(t_ph *philo, int flag);
char	*ft_itoa(int n);
void	*kill_check(void *ptr);
void	*monitor(void *ptr);
int		stop_dinner(t_ph *philo);

#endif
