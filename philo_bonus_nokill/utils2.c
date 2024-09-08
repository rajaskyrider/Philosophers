/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpandipe <rpandie@student.42luxembourg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 22:44:02 by rpandipe          #+#    #+#             */
/*   Updated: 2024/09/09 01:38:10 by rpandipe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	int_count(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

int	ft_abs(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

char	*ft_itoa(int n)
{
	char	*ans;
	int		count;

	count = int_count(n);
	ans = (char *)malloc(sizeof(char) * (count + 2));
	if (!ans)
		return (NULL);
	ans[count + 1] = '\0';
	count--;
	ans[0] = '/';
	if (n == 0)
		ans[1] = '0';
	if (n < 0)
		ans[0] = '-';
	while (n != 0)
	{
		ans[count + 1] = ft_abs(n % 10) + '0';
		n = n / 10;
		count--;
	}
	return (ans);
}

size_t	get_current_time(t_ph *philo)
{
	struct timeval	time;
	int				i;

	i = 0;
	if (gettimeofday(&time, NULL) == -1)
	{
		while (++i < philo->count)
			sem_post(philo->dead_lock);
		return (0);
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t ms, t_ph *philo)
{
	size_t	start;
	size_t	end;

	start = get_current_time(philo);
	end = start + ms;
	while (get_current_time(philo) < end)
		usleep(100);
	return (TRUE);
}
