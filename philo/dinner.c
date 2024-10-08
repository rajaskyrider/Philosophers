/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:44:42 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/28 18:44:01 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dinner(t_table *table, pthread_mutex_t	*fork)
{
	pthread_t	waiter;
	int			i;

	i = 0;
	if (pthread_create(&waiter, NULL, &monitor, table) != 0)
		return (destroy_mutex(table, fork, table->philo[0].count), FALSE);
	while (i < table->philo[0].count)
	{
		if (pthread_create(&table->philo[i].thread, NULL, \
			&routine, &table->philo[i]) != 0)
			return (destroy_mutex(table, fork, table->philo[0].count), FALSE);
		i++;
	}
	if (pthread_join(waiter, NULL) != 0)
		return (destroy_mutex(table, fork, table->philo[0].count), FALSE);
	i = 0;
	while (i < table->philo[0].count)
	{
		if (pthread_join(table->philo[i].thread, NULL) != 0)
			return (destroy_mutex(table, fork, table->philo[0].count), FALSE);
		i++;
	}
	return (TRUE);
}
