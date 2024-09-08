/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:44:42 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/09 01:41:00 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	setup_routine(t_ph *philo)
{
	pthread_t	monitor_thd;
	pthread_t	checker_thd;
	pthread_t	routine_thd;
	char		*sem_name;

	sem_name = ft_itoa(philo->id);
	sem_unlink(sem_name);
	philo->flag_lock = sem_open(sem_name, O_CREAT | O_EXCL, S_IRWXU, 1);
	free(sem_name);
	if (philo->flag_lock == SEM_FAILED)
		return (ft_sem_close(philo, 6), FALSE);
	pthread_create(&routine_thd, NULL, &routine, philo);
	pthread_create(&checker_thd, NULL, &kill_check, philo);
	pthread_create(&monitor_thd, NULL, &monitor, philo);
	pthread_join(routine_thd, NULL);
	pthread_join(checker_thd, NULL);
	pthread_join(monitor_thd, NULL);
	sem_close(philo->flag_lock);
	return (TRUE);
}

void	stop_thd(t_ph *philo, int *pid)
{
	int	i;

	i = -1;
	while (++i < philo->count)
		sem_wait(philo->dine_lock);
	i = -1;
	while (++i < philo->count)
		sem_post(philo->dead_lock);
	sem_post(philo->write_lock);
	i = -1;
	while (++i < philo->count)
		waitpid(pid[i], NULL, 0);
	ft_sem_close(philo, 6);
}

int	dinner(t_ph *philo)
{
	int			i;
	pid_t		pid[PHILO_MAX];

	i = -1;
	while (++i < philo->count)
	{
		philo->id = i + 1;
		pid[i] = fork();
		if (pid[i] == 0)
		{
			setup_routine(philo);
			exit (TRUE);
		}
		else if (pid[i] < 0)
		{
			ft_sem_close(philo, 6);
			exit (FALSE);
		}
	}
	stop_thd(philo, pid);
	return (TRUE);
}
