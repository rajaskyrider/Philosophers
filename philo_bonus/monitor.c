/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:17:35 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/09 10:48:41 by rpandipe         ###   ########.fr       */
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
	while (c < philo->count)
	{
		sem_wait(philo->dine_lock);
		c++;
	}
	while (++i < philo->count)
		kill(philo->pid[i], SIGKILL);
	return (ptr);
}
