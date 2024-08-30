/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:42:35 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/30 16:48:44 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(t_ph *philo)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		sem_post(philo->dead_lock);
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
	sem_wait(philo->write_lock);
	if (philo->write_lock == 0)
		printf("%zu %d %s\n", time, id, str);
	sem_post(philo->write_lock);
}
