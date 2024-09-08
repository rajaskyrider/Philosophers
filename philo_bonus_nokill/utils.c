/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:42:35 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/08 14:42:38 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(int id, char *str, t_ph *philo)
{
	size_t	time;

	time = get_current_time(philo) - philo->start_time;
	sem_wait(philo->write_lock);
	if (!(stop_dinner(philo)))
		printf("%zu %d %s\n", time, id, str);
	sem_post(philo->write_lock);
}

void	ft_sem_close(t_ph *philo, int flag)
{
	if (flag > 0)
		sem_close(philo->forks);
	if (flag > 1)
		sem_close(philo->waiter1);
	if (flag > 2)
		sem_close(philo->waiter2);
	if (flag > 3)
		sem_close(philo->write_lock);
	if (flag > 4)
		sem_close(philo->dine_lock);
	if (flag > 5)
		sem_close(philo->dead_lock);
	sem_unlink("/fork");
	sem_unlink("/write_lock");
	sem_unlink("/dine_lock");
	sem_unlink("/dead_lock");
	sem_unlink("/waiter1");
	sem_unlink("/waiter2");
}

int	stop_dinner(t_ph *philo)
{
	int	stop;

	sem_wait(philo->flag_lock);
	stop = philo->must_die;
	sem_post(philo->flag_lock);
	return (stop);
}
