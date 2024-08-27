/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 22:27:01 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/27 11:21:55 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	starvation(t_ph *philo, int i)
{
	int	result;

	result = FALSE;
	pthread_mutex_lock(philo[i].meal_lock);
	if ((get_current_time(philo) - philo[i].last_meal) > philo[i].time_to_die)
		result = TRUE;
	pthread_mutex_unlock(philo[i].meal_lock);
	return (result);
}

int	check_health(t_ph *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].count)
	{
		if (starvation(philo, i) == TRUE)
		{
			print_status(philo[i].id, "died", philo);
			pthread_mutex_lock(philo[i].dead_lock);
			*philo[i].dead_flag = 1;
			pthread_mutex_unlock(philo[i].dead_lock);
			return (FALSE);
		}
		i++;
	}
	return (TRUE);
}

int	check_meal(t_ph	*philo)
{
	int	i;
	int	ate;

	i = 0;
	ate = 0;
	if (philo[i].dine_count == -1)
		return (FALSE);
	while (i < philo[0].count)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].ate > philo[i].dine_count)
			ate++;
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	if (ate == philo[0].count)
	{
		pthread_mutex_lock(philo[0].dead_lock);
		*philo[0].dead_flag = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (TRUE);
	}
	return (FALSE);
}

int	check_error(t_table	*table)
{
	int	result;

	result = FALSE;
	pthread_mutex_lock(&table->error_lock);
	if (table->error_flag == 1)
		result = TRUE;
	pthread_mutex_unlock(&table->error_lock);
	return (result);
}

void	*monitor(void *ptr)
{
	t_table	*table;

	table = (t_table *)ptr;
	while (TRUE)
	{
		if (check_health(table->philo) == FALSE || check_meal(table->philo) == TRUE \
			|| check_error(table) == TRUE)
			break;
	}
	return (ptr);
}