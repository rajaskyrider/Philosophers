/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:50:00 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/25 22:25:46 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_table			table;
	t_ph			philo[PHILO_MAX];
	pthread_mutex_t	fork[PHILO_MAX];

	if (!check_input(argc, argv) || \
		!init(&table, philo, fork, argv))
		return (1);
	if (!dinner(&table, fork))
		return (1);
	destroy_mutex(&table, fork, table.philo[0].count);
	return (0);
}
