/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:42:35 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/28 18:44:27 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_table *table, pthread_mutex_t *fork, int count)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->dead_lock);
	pthread_mutex_destroy(&table->error_lock);
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->meal_lock);
	while (i < count)
	{
		pthread_mutex_destroy(&fork[i]);
		i++;
	}
}

size_t	get_current_time(t_ph *philo)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		pthread_mutex_lock(philo->error_lock);
		*philo->error_flag = 1;
		pthread_mutex_unlock(philo->error_lock);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms, t_ph *philo)
{
	size_t	start;
	size_t	end;

	start = get_current_time(philo);
	end = start + ms;
	while (get_current_time(philo) < end)
		usleep(100);
	return (TRUE);
}

void	print_status(int id, char *str, t_ph *philo)
{
	size_t	time;

	time = get_current_time(philo) - philo->start_time;
	pthread_mutex_lock(philo->write_lock);
	if (check_dead(philo) == FALSE)
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}
