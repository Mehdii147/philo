/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:41:43 by ehafiane          #+#    #+#             */
/*   Updated: 2024/10/03 16:30:56 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_msleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(100);
}

int	result(char *s, int i, int sign)
{
	long long	r;

	r = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (r > INT_MAX)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		r = r * 10 + (s[i] - '0');
		i++;
	}
	return (r);
}

int	ft_atoi(char *str)
{
	int					i;
	long long			r;
	int					s;

	i = 0;
	s = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	r = result(str, i, s);
	return (r * s);
}

long long	ll_result(char *s, int i, int sign)
{
	long long	r;

	r = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (r > LONG_MAX / 10
			|| (r == LONG_MAX / 10 && (s[i] - '0') > LONG_MAX % 10))
		{
			if (sign == -1)
				return (LLONG_MIN);
			return (LLONG_MAX);
		}
		r = r * 10 + (s[i] - '0');
		i++;
	}
	return (r);
}

long long	ft_atoll(char *str)
{
	int			i;
	long long	r;
	int			s;

	i = 0;
	s = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	r = ll_result(str, i, s);
	return (r * s);
}
