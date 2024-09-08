/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:50:00 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/09 01:41:44 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_fork(t_ph *philo, int count)
{
	sem_unlink("/fork");
	philo->forks = sem_open("/fork", O_CREAT | O_EXCL, S_IRWXU, count);
	if (philo->forks == SEM_FAILED)
		return (FALSE);
	return (TRUE);
}

int	init_sems(t_ph *philo)
{
	sem_unlink("/write_lock");
	sem_unlink("/dine_lock");
	sem_unlink("/dead_lock");
	sem_unlink("/waiter1");
	sem_unlink("/waiter2");
	philo->waiter1 = sem_open("/waiter1", O_CREAT | O_EXCL, S_IRWXU, \
							philo->count / 2 + (philo->count == 1));
	if (philo->waiter1 == SEM_FAILED)
		return (ft_sem_close(philo, 1), FALSE);
	philo->waiter2 = sem_open("/waiter2", O_CREAT | O_EXCL, S_IRWXU, \
							philo->count / 2);
	if (philo->waiter2 == SEM_FAILED)
		return (ft_sem_close(philo, 2), FALSE);
	philo->write_lock = sem_open("/write_lock", O_CREAT | O_EXCL, S_IRWXU, 1);
	if (philo->write_lock == SEM_FAILED)
		return (ft_sem_close(philo, 3), FALSE);
	philo->dine_lock = sem_open("/dine_lock", O_CREAT | O_EXCL, S_IRWXU, 0);
	if (philo->dine_lock == SEM_FAILED)
		return (ft_sem_close(philo, 4), FALSE);
	philo->dead_lock = sem_open("/dead_lock", O_CREAT | O_EXCL, S_IRWXU, 0);
	if (philo->dead_lock == SEM_FAILED)
		return (ft_sem_close(philo, 5), FALSE);
	return (TRUE);
}

int	main(int argc, char **argv)
{
	t_ph	philo;

	if (!check_input(argc, argv))
		return (1);
	philo.eating = 0;
	philo.ate = 0;
	philo.count = ft_atoi(argv[1]);
	philo.time_to_die = ft_atoi(argv[2]);
	philo.time_to_eat = ft_atoi(argv[3]);
	philo.time_to_sleep = ft_atoi(argv[4]);
	philo.dine_count = -1;
	if (argv[5])
		philo.dine_count = ft_atoi(argv[5]);
	philo.error_flag = 0;
	if (!init_sems(&philo) || !init_fork(&philo, ft_atoi(argv[1])))
		return (FALSE);
	philo.start_time = get_current_time(&philo);
	philo.last_meal = get_current_time(&philo);
	philo.must_die = 0;
	dinner(&philo);
	return (0);
}
