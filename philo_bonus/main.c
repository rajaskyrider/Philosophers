/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:50:00 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/18 11:34:48 by rpandipe         ###   ########.fr       */
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
		dprintf(2, "\033[31mWaiting for write lock in check monitor\n\033[0m\n");
		sem_wait(philo->write_lock);
		dprintf(2, "\033[31mRecieved write lock in check_monitor\n\033[0m\n");
		printf("%zu %d died\n", get_current_time()
			- philo->start_time, philo->id);
		philo->stop = 1;
		exit (1);
	}
}

void	dinner(t_ph *philo)
{
	if (philo->id % 2 == 0)
		usleep(1000);
	while (philo->ate < philo->dine_count)
	{
		print_status(philo->id, "is thinking", philo);
		if (philo->count == 1)
		{
			dprintf(2, "\033[31mWaiting for forks in dinner\n\033[0m\n");
			sem_wait(philo->forks);
			dprintf(2, "\033[31mRecieved forks in dinner\n\033[0m\n");
			print_status(philo->id, "has taken a fork", philo);
			ft_usleep(philo->time_to_die, philo);
			dprintf(2, "\033[31mPosting forks in dinner\n\033[0m\n");
			sem_post(philo->forks);
			//dprintf(2,"\033[31mPosting fork from dinner(1) \033[0m\n");
			//print_status(philo->id, "checking monitor", philo);
			check_monitor(philo);
			print_status(philo->id, "Done monitor", philo);
		}
		dprintf(2, "\033[31mWaiting for max eater dinner\n\033[0m\n");
		sem_wait(philo->max_eater);
		dprintf(2, "\033[31mRecieved max eater in dinner\n\033[0m\n");
		dprintf(2, "\033[31mWaiting for forks in dinner\n\033[0m\n");
		sem_wait(philo->forks);
		dprintf(2, "\033[31mRecieved forks in dinner\n\033[0m\n");
		print_status(philo->id, "has taken a fork", philo);
		check_monitor(philo);
		dprintf(2, "\033[31mWaiting for forks in dinner\n\033[0m\n");
		sem_wait(philo->forks);
		dprintf(2, "\033[31mRecieved forks in dinner\n\033[0m\n");
		print_status(philo->id, "has taken a fork", philo);
		print_status(philo->id, "is eating", philo);
		philo->last_meal = get_current_time();
		ft_usleep(philo->time_to_eat, philo);
		dprintf(2, "\033[31mPosting forks in dinner\n\033[0m\n");
		sem_post(philo->forks);
		dprintf(2, "\033[31mPosting forks in dinner\n\033[0m\n");
		sem_post(philo->forks);
		dprintf(2, "\033[31mPosting max_eater in dinner\n\033[0m\n");
		sem_post(philo->max_eater);
		if (++(philo->ate) == philo->dine_count)
		{
			printf("Thread %d: posting to semaphore from dinner\n", philo->id);
			dprintf(2, "\033[31mPosting dine lock in dinner\n\033[0m\n");
			sem_post(philo->dine_lock);
		}
		print_status(philo->id, "is sleeping", philo);
		ft_usleep(philo->time_to_sleep, philo);
	}
}

void	exit_philo(t_ph *philo, int	*pid)
{
	int	i;
	int	status;

	i = 0;
	pthread_create(&philo->monitor, NULL, &meal_check, philo);
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
				{
					printf("Thread %d: posting to semaphore from exit\n", i);
					dprintf(2, "\033[31mPosting dine lock in dinner\n\033[0m\n");
					sem_post(philo->dine_lock);
				}
			break ;
		}
		i++;
	}
	if (pthread_join(philo->monitor, NULL))
		print_error("Error: Failed to join the thread");
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
