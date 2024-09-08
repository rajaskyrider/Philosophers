/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:27:01 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/09 01:38:59 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	starvation(t_ph *philo)
{
	int		result;

	result = FALSE;
	sem_wait(philo->flag_lock);
	if ((get_current_time(philo) - philo->last_meal) >= philo->time_to_die)
		result = TRUE;
	sem_post(philo->flag_lock);
	return (result);
}

void	*monitor(void *ptr)
{
	t_ph	*philo;
	int		i;

	philo = (t_ph *)ptr;
	while (!stop_dinner(philo))
	{
		usleep(100);
		sem_wait(philo->write_lock);
		if (!stop_dinner(philo) && starvation(philo))
		{
			printf("%zu %d died\n", get_current_time(philo)
				- philo->start_time, philo->id);
			i = 0;
			while (i++ < philo->count)
				sem_post(philo->dead_lock);
			return (ptr);
		}
		sem_post(philo->write_lock);
	}
	return (ptr);
}
