/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:17:35 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/18 13:01:57 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*meal_check(void *ptr)
{
	int		c;
	int		i;
	t_ph	*philo;

	c = 0;
	i = -1;
	philo = (t_ph *)ptr;
	if (philo->dine_count == -1)
		return (ptr);
	while (c < philo->count)
	{
		sem_wait(philo->dine_lock);
		c++;
	}
	while (++i < philo->count)
		kill(philo->pid[i], SIGKILL);
	return (ptr);
}
