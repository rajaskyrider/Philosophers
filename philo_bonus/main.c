/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:50:00 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/09 01:37:12 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	int	ans;
	int	sign;
	int	i;

	ans = 0;
	sign = 1;
	i = 0;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32)
		i++;
	if ((nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		ans = ans * 10 + (nptr[i] - '0');
		i++;
	}
	return (sign * ans);
}

void	*check_monitor(void	*ptr)
{
	t_ph	*philo;

	philo = (t_ph *)ptr;
	while (!philo->stop)
	{
		usleep(100);
		if (get_current_time() - philo->last_meal > philo->time_to_die)
		{
			philo->dead = 1;
			sem_wait(philo->write_lock);
			printf("%zu %d died\n", get_current_time()
				- philo->start_time, philo->id);
			philo->stop = 1;
			break ;
		}
		if (philo->dine_count != -1 && philo->ate >= philo->dine_count)
		{
			philo->stop = 1;
			break ;
		}
	}
	if (philo->dead)
		exit (1);
	exit (0);
}

void	dinner(t_ph *philo)
{
	if (pthread_create(&philo->monitor, NULL, &check_monitor, philo))
		print_error("Error: Failed to create thread");
	if (philo->id % 2 == 1)
		usleep(1000);
	while (TRUE)
	{
		print_status(philo->id, "is thinking", philo);
		sem_wait(philo->forks);
		print_status(philo->id, "has taken a fork", philo);
		sem_wait(philo->forks);
		print_status(philo->id, "has taken a fork", philo);
		print_status(philo->id, "is eating", philo);
		ft_usleep(philo->time_to_eat, philo);
		philo->last_meal = get_current_time();
		sem_post(philo->forks);
		sem_post(philo->forks);
		philo->ate += 1;
		print_status(philo->id, "is sleeping", philo);
		ft_usleep(philo->time_to_sleep, philo);
	}
	if (pthread_join(philo->monitor, NULL))
		print_error("Error: Failed to join the thread");
}

void	exit_philo(t_ph *philo, int	*pid)
{
	int	i;
	int	status;

	i = 0;
	while (i < philo->count)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = -1;
			while (++i < philo->count)
				kill(pid[i], SIGKILL);
			break ;
		}
		i++;
	}
	ft_sem_close(philo, 3);
	free(philo);
}

int	main(int argc, char **argv)
{
	t_ph	*philo;
	int		i;
	int		pid[PHILO_MAX];

	philo = init_philo(argc, argv);
	i = -1;
	philo->start_time = get_current_time();
	while (++i < philo->count)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			print_error("Error creating fork\n");
		if (pid[i] == 0)
		{
			philo->id = i + 1;
			philo->last_meal = get_current_time();
			dinner (philo);
		}
	}
	exit_philo(philo, pid);
	return (0);
}
