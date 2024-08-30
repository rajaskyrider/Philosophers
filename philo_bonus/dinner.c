/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 21:44:42 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/30 14:14:42 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dessert(int *pid, int flag, int count)
{
	int		i;
	pid_t	dead_pid;
	int		status;
	
	i = 0;
	if (flag != 0)
		exit_child(pid, pid[flag], count);
	while ((dead_pid = waitpid(-1, &status, WNOHANG)> 0))
	{
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit_child(pid, dead_pid, count);
	}
}

void	dinner(t_ph *philo, int count)
{
	pthread_t	waiter;
	int			i;
	pid_t		pid[PHILO_MAX];
	int			result;

	i = 0;
	while (i < philo->count)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			result = routine(&philo[i]);
			exit(result);
		}
		else if (pid[i] < 0)
			break;
		i++;
	}
	if (i == count)
		i = 0;
	//dessert(pid, i, count);
}
