 /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:36:17 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/30 15:43:00 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_ph *philo)
{
	print_status(philo->id, "is thinking", philo);
}

void	sleepy(t_ph *philo)
{
	print_status(philo->id, "is sleeping", philo);
	ft_usleep(philo->time_to_sleep, philo);
}

void	eat(t_ph *philo)
{
	sem_wait(philo->forks);
	print_status(philo->id, "has taken a fork", philo);
	if (philo->count == 1)
	{
		ft_usleep(philo->time_to_die, philo);
		sem_post(philo->forks);
		exit (FALSE) ;
	}
	sem_wait(philo->forks);
	print_status(philo->id, "has taken a fork", philo);
	if (philo->must_die == 0)
	{
		philo->eating = 1;
		print_status(philo->id, "is eating", philo);
		philo->last_meal = get_current_time(philo);
		philo->ate++;
		ft_usleep(philo->time_to_eat, philo);
		philo->eating = 0;
	}	
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	kill_check(t_ph *philo)
{
	sem_wait(philo->dead_lock);
	sem_post(philo->dead_lock);
	sem_wait(philo->write_lock);
	philo->must_die = 1;
	while (philo->eating == 1)
		usleep(10);
	sem_post(philo->write_lock);
	exit(EXIT_SUCCESS);

}

void	routine(t_ph *philo)
{
	pthread_t	monitor;
	
	pthread_create(&monitor, NULL, &kill_check, philo);
	if (philo->id % 2 == 0)
		ft_usleep(1, philo);
	while (philo->must_die == 0)
	{
		eat(philo);
		if (philo->dine_count == philo->ate)
		{
			sem_post(philo->dine_lock);
			break ;
		}
		sleepy(philo);
		think(philo);
	}
	pthread_join(monitor, NULL);
}
