/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:31:27 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/28 18:43:15 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_table(t_table *table, t_ph *philo)
{
	table->dead_flag = 0;
	table->error_flag = 0;
	if (pthread_mutex_init(&table->dead_lock, NULL) != 0)
		return (FALSE);
	else if (pthread_mutex_init(&table->error_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->dead_lock);
		return (FALSE);
	}
	else if (pthread_mutex_init(&table->write_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->dead_lock);
		pthread_mutex_destroy(&table->error_lock);
		return (FALSE);
	}
	else if (pthread_mutex_init(&table->meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&table->dead_lock);
		pthread_mutex_destroy(&table->error_lock);
		pthread_mutex_destroy(&table->write_lock);
		return (FALSE);
	}
	table->philo = philo;
	return (TRUE);
}

int	init_fork(pthread_mutex_t *fork, int count, t_table *table)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
			return (destroy_mutex(table, fork, i), FALSE);
		i++;
	}
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

int	init_philo(t_table *table, t_ph *philo, pthread_mutex_t *fork, char **argv)
{
	int	i;
	int	count;

	i = 0;
	count = ft_atoi(argv[1]);
	while (i < count)
	{
		philo[i].id = i + 1;
		philo[i].eating = 0;
		set_args(&philo[i], argv);
		philo[i].dead_flag = &table->dead_flag;
		philo[i].error_flag = &table->error_flag;
		if (i == 0)
			philo[i].rfork = &fork[count - 1];
		else
			philo[i].rfork = &fork[i - 1];
		philo[i].lfork = &fork[i];
		philo[i].dead_lock = &table->dead_lock;
		philo[i].error_lock = &table->error_lock;
		philo[i].write_lock = &table->write_lock;
		philo[i].meal_lock = &table->meal_lock;
		i++;
	}
	return (TRUE);
}

int	init(t_table *table, t_ph *philo, pthread_mutex_t *fork, char **argv)
{
	if (!init_table(table, philo) || \
		!init_fork(fork, ft_atoi(argv[1]), table) || \
		!init_philo(table, philo, fork, argv))
		return (FALSE);
	return (TRUE);
}
