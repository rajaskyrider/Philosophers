/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandipe.student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:39:48 by rpandipe          #+#    #+#             */
/*   Updated: 2024/08/09 14:18:16 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	print_error(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	write(2, "\n", 2);
}

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
