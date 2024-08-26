/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:27:01 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/25 22:40:54 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *ptr)
{
	t_ph	*philo;

	philo = (t_ph *)ptr;
	while (TRUE)
	{
		if (check_health(philo) == FALSE || check_meal(philo) == TRUE \
			|| check_error(philo) == TRUE)
			break;
	}
	return (ptr);
			
}