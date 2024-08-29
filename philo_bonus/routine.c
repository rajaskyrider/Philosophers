/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:36:17 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/29 15:38:15 by rpandipe         ###   ########.fr       */
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
	pthread_mutex_lock(philo->rfork);
	print_status(philo->id, "has taken a fork", philo);
	if (philo->count == 1)
	{
		ft_usleep(philo->time_to_die, philo);
		pthread_mutex_unlock(philo->rfork);
		return ;
	}
	pthread_mutex_lock(philo->lfork);
	print_status(philo->id, "has taken a fork", philo);
	philo->eating = 1;
	print_status(philo->id, "is eating", philo);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time(philo);
	philo->ate++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat, philo);
	philo->eating = 0;
	pthread_mutex_unlock(philo->rfork);
	pthread_mutex_unlock(philo->lfork);
}

int	routine(t_ph *philo)
{
	if (philo->id % 2 == 0)
		ft_usleep(1, philo);
	while (check_dead(philo) == FALSE)
	{
		eat(philo);
		sleepy(philo);
		think(philo);
	}
	return (ptr);
}