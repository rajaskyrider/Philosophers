/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:02:43 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/18 13:05:07 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	deal_one(t_ph *philo)
{
	sem_wait(philo->forks);
	print_status(philo->id, "has taken a fork", philo);
	ft_usleep(philo->time_to_die, philo);
	sem_post(philo->forks);
	check_monitor(philo);
}