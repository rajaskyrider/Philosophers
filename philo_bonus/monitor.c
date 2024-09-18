/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 10:17:35 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/18 11:29:00 by rpandipe         ###   ########.fr       */
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
	printf("Starting to wait\n");
	while (c < philo->count)
	{
		dprintf(2, "\033[32mWaiting for dine lock\n\033[0m\n");
		sem_wait(philo->dine_lock);
		dprintf(2, "\033[32mThread %d: Recieved dine lock in monitor\033[0m\n", c + 1);
		c++;
	}
	while (++i < philo->count)
		kill(philo->pid[i], SIGKILL);
	return (ptr);
}
