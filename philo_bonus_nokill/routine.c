/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:36:17 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/09 01:44:27 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	deal_one(t_ph *philo)
{
	ft_usleep(philo->time_to_die, philo);
	sem_post(philo->forks);
	sem_post(philo->waiter1);
}

void	sleepy(t_ph *philo)
{
	print_status(philo->id, "is sleeping", philo);
	ft_usleep(philo->time_to_sleep, philo);
}

void	eat(t_ph *philo)
{
	sem_wait(philo->waiter1);
	sem_wait(philo->forks);
	print_status(philo->id, "has taken a fork", philo);
	if (philo->count == 1)
	{
		deal_one(philo);
		return ;
	}
	sem_wait(philo->waiter2);
	sem_wait(philo->forks);
	print_status(philo->id, "has taken a fork", philo);
	sem_post(philo->waiter2);
	if (stop_dinner(philo) == 0)
	{
		print_status(philo->id, "is eating", philo);
		sem_wait(philo->flag_lock);
		philo->last_meal = get_current_time(philo);
		sem_post(philo->flag_lock);
		sem_post(philo->waiter1);
		ft_usleep(philo->time_to_eat, philo);
		if (philo->ate++ == philo->dine_count)
			sem_post(philo->dine_lock);
	}
	sem_post(philo->forks);
	sem_post(philo->forks);
}

void	*kill_check(void *ptr)
{
	t_ph	*philo;

	philo = (t_ph *)ptr;
	sem_wait(philo->dead_lock);
	sem_wait(philo->flag_lock);
	philo->must_die = 1;
	sem_post(philo->flag_lock);
	sem_post(philo->dine_lock);
	return (ptr);
}

void	*routine(void *ptr)
{
	t_ph	*philo;

	philo = (t_ph *)ptr;
	while (!(stop_dinner(philo)))
	{
		eat(philo);
		sleepy(philo);
		print_status(philo->id, "is thinking", philo);
	}
	return (ptr);
}
