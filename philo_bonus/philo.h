/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:51:08 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/09 01:37:30 by rpandipe         ###   ########.fr       */
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
	int				stop;
	int				count;
	int				ate;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	long			dine_count;
	size_t			start_time;
	size_t			last_meal;
	sem_t			*forks;
	sem_t			*write_lock;
	sem_t			*dine_lock;
	int				dead;
	pthread_t		monitor;
}	t_ph;

t_ph	*init_philo(int argc, char **argv);
int		ft_atoi(const char *nptr);
void	ft_sem_close(t_ph *philo, int flag);
void	print_error(char *str);
void	print_status(int id, char *str, t_ph *philo);
void	ft_usleep(size_t ms, t_ph *philo);
size_t	get_current_time(void);

#endif
