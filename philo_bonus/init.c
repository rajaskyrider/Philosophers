/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:31:27 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/30 16:03:12 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_fork(sem_t *fork, int count)
{
	fork = sem_open("/fork", O_CREAT, 0644, count);
	if (fork == SEM_FAILED)
		return (FALSE);
	return (TRUE);
}

void	set_args(t_ph *philo, char **argv)
{
	philo->ate = 0;
	philo->count = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->dine_count = -1;
	if (argv[5])
		philo->dine_count = ft_atoi(argv[5]);
	philo->start_time = get_current_time(philo);
	philo->last_meal = get_current_time(philo);
}

void	init_sems(t_ph *philo)
{
	sem_t	*write_lock;
	sem_t	*dine_lock;
	sem_t	*dead_lock;

	write_lock = sem_open("/write_lock", O_CREAT, 0644, 1);
	dine_lock = sem_open("/dine_lock", O_CREAT, 0644, 0);
	dead_lock = sem_open("/error_lock", O_CREAT, 0644, 0);
	if (dine_lock == SEM_FAILED || write_lock == SEM_FAILED \
		|| dead_lock == SEM_FAILED)
		exit(1);
	philo->write_lock = write_lock;
	philo->dine_lock = dine_lock;
	philo->dead_lock = dead_lock;
}

int	init_philo(t_ph *philo, pthread_mutex_t *fork, char **argv)
{
	int		i;
	int		count;

	i = 0;
	count = ft_atoi(argv[1]);
	while (i < count)
	{
		philo[i].id = i + 1;
		philo[i].eating = 0;
		set_args(&philo[i], argv);
		philo[i].error_flag = 0;
		init_sems(&philo[i]);
		philo[i].forks = fork;
		philo[i].must_die = 0;
		i++;
	}
	return (TRUE);
}

int	init(t_ph *philo, sem_t *fork, char **argv)
{
	if (!init_fork(fork, ft_atoi(argv[1])) || \
		!init_philo(philo, fork, argv))
		return (FALSE);
	return (TRUE);
}
