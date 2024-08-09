/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:51:08 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/09 15:30:31 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

# define TRUE 0
# define FALSE 1
# define PHILO_MAX 200

typedef struct s_ph
{
	pthread_t		thread;
	int				id;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				dine_count;
	int				*dead_flag;
	pthread_mutex_t	*rfork;
	pthread_mutex_t	*lfork;
	pthread_mutex_t	*write_lock;

}	t_ph;

int	check_input(int argc, char **argv);

#endif
