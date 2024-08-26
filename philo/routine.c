/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:09:03 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/26 16:23:13 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(t_ph *philo)
{
	int	result;

	result = FALSE;
	pthread_mutex_lock(philo->dead_lock);
	if (philo->dead_flag == 1)
		result = TRUE;
	pthread_mutex_unlock(philo->dead_lock);
	return (result);
}

void	think(t_ph *philo)
{
	print_status(philo->id, "is thinking", philo);
}

void	sleep(t_ph *philo)
{
	print_status(philo->id, "is sleeping", philo);
	ft_usleep(philo->time_to_sleep, philo);
}

void	eat(t_ph *philo)
{
	pthread_mutex_lock(philo->rfork);
	print_status(philo->id, "has taken the fork", philo);
	if (philo->count == 1)
	{
		ft_usleep(philo->time_to_die, philo);
		pthread_mutex_unlock(philo->rfork);
		return ;
	}
	pthread_mutex_lock(philo->lfork);
	print_status(philo->id, "has taken the fork", philo);
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

void	*routine(void *ptr)
{
	t_ph *philo;

	philo = (t_ph *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(1, philo);
	while (check_dead(philo) == FALSE)
	{
		eat(philo);
		sleep(philo);
		think(philo);
	}
	return (ptr);
}