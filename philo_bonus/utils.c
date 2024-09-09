/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:56:32 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/09 10:43:52 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sem_close(t_ph *philo, int flag)
{
	if (flag > 0)
		sem_close(philo->forks);
	if (flag > 1)
		sem_close(philo->write_lock);
	if (flag > 2)
		sem_close(philo->dine_lock);
	sem_unlink("/fork");
	sem_unlink("/write_lock");
	sem_unlink("/dine_lock");
}

void	print_status(int id, char *str, t_ph *philo)
{
	size_t	time;

	time = get_current_time() - philo->start_time;
	sem_wait(philo->write_lock);
	if (!philo->stop)
		printf("%zu %d %s\n", time, id, str);
	sem_post(philo->write_lock);
}

void	print_error(char *str)
{
	int	i;

	i = 0;
	while (*(str + i))
		i++;
	write(2, str, i);
	write(2, "\n", 1);
	exit(0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(size_t ms, t_ph *philo)
{
	size_t	start;
	size_t	end;

	start = get_current_time();
	end = start + ms;
	while (get_current_time() < end)
	{
		check_monitor(philo);
		usleep(100);
	}
}
