/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:50:46 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/17 12:30:31 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	check_input(int argc, char **argv)
{
	(void) argv;
	if (argc != 5 && argc != 6)
		return (print_error("Please enter the required arguments"), \
				FALSE);
	else if (check_arg(argv[1]) == FALSE || ft_atoi(argv[1]) <= 0 \
			|| ft_atoi(argv[1]) > PHILO_MAX)
		return (print_error("number_of_philosophers is invalid"), FALSE);
	else if (check_arg(argv[2]) == FALSE || ft_atoi(argv[2]) <= 0)
		return (print_error("time_to_die is invalid"), FALSE);
	else if (check_arg(argv[3]) == FALSE || ft_atoi(argv[3]) <= 0)
		return (print_error("time_to_eat is invalid"), FALSE);
	else if (check_arg(argv[4]) == FALSE || ft_atoi(argv[4]) <= 0)
		return (print_error("time_to_sleep is invalid"), FALSE);
	else if (argc == 6 && \
			(check_arg(argv[5]) == FALSE || ft_atoi(argv[5]) <= 0))
		return (print_error \
			("number_of_times_each_philosopher_must_eat is invalid"), FALSE);
	else
		return (TRUE);
}

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
	sem_unlink("/max_eater");
	philo->max_eater = sem_open("/max_eater", O_CREAT | O_EXCL, S_IRWXU, \
							(philo->count - 1 ) + (philo->count == 1));
	if (philo->max_eater == SEM_FAILED)
		return (ft_sem_close(philo, 1), FALSE);
	philo->write_lock = sem_open("/write_lock", O_CREAT | O_EXCL, S_IRWXU, 1);
	if (philo->write_lock == SEM_FAILED)
		return (ft_sem_close(philo, 2), FALSE);
	philo->dine_lock = sem_open("/dine_lock", O_CREAT | O_EXCL, S_IRWXU, 0);
	if (philo->dine_lock == SEM_FAILED)
		return (ft_sem_close(philo, 3), FALSE);
	return (TRUE);
}

t_ph	*init_philo(int argc, char **argv, t_ph *philo)
{
	if (!check_input(argc, argv))
		exit(1);
	philo->stop = 0;
	philo->ate = 0;
	philo->count = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->dine_count = -1;
	if (argv[5])
		philo->dine_count = ft_atoi(argv[5]);
	if (!init_fork(philo, ft_atoi(argv[1])) || !init_sems(philo))
		return (FALSE);
	philo->dead = 0;
	return (philo);
}
