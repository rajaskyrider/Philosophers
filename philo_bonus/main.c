/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:50:00 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/18 13:27:28 by rpandipe         ###   ########.fr       */
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

void	check_monitor(t_ph	*philo)
{
	if (get_current_time() - philo->last_meal >= philo->time_to_die)
	{
		philo->dead = 1;
		sem_wait(philo->write_lock);
		printf("%zu %d died\n", get_current_time()
			- philo->start_time, philo->id);
		philo->stop = 1;
		exit (1);
	}
}

void	dinner(t_ph *philo)
{
	usleep((philo->id % philo->count) * 1000);
	while (TRUE)
	{
		print_status(philo->id, "is thinking", philo);
		if (philo->count == 1)
			deal_one(philo);
		sem_wait(philo->max_eater);
		sem_wait(philo->forks);
		print_status(philo->id, "has taken a fork", philo);
		check_monitor(philo);
		sem_wait(philo->forks);
		print_status(philo->id, "has taken a fork", philo);
		sem_post(philo->max_eater);
		check_monitor(philo);
		print_status(philo->id, "is eating", philo);
		philo->last_meal = get_current_time();
		ft_usleep(philo->time_to_eat, philo);
		sem_post(philo->forks);
		sem_post(philo->forks);
		if (++(philo->ate) == philo->dine_count)
			sem_post(philo->dine_lock);
		print_status(philo->id, "is sleeping", philo);
		ft_usleep(philo->time_to_sleep, philo);
	}
}

void	exit_philo(t_ph *philo, int	*pid)
{
	int	i;
	int	status;
	int	m_pid;

	i = 0;
	m_pid = create_monitor(philo);
	while (i < philo->count)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			i = -1;
			if (philo->dine_count == -1)
				while (++i < philo->count)
					kill(pid[i], SIGKILL);
			else
				while (++i < philo->count)
					sem_post(philo->dine_lock);
			break ;
		}
		i++;
	}
	waitpid(m_pid, NULL, 0);
	ft_sem_close(philo, 3);
}

int	main(int argc, char **argv)
{
	t_ph	philo;
	int		i;

	init_philo(argc, argv, &philo);
	i = -1;
	philo.start_time = get_current_time();
	while (++i < philo.count)
	{
		philo.pid[i] = fork();
		if (philo.pid[i] == -1)
			print_error("Error creating fork\n");
		if (philo.pid[i] == 0)
		{
			philo.id = i + 1;
			philo.last_meal = get_current_time();
			dinner (&philo);
		}
	}
	exit_philo(&philo, philo.pid);
	return (0);
}
