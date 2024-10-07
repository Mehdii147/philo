/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:19:35 by ehafiane          #+#    #+#             */
/*   Updated: 2024/10/06 22:52:55 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_nb_arg(int ac)
{
	if (ac != 5 && ac != 6)
		return (0);
	return (1);
}

int	check_arg_syntax(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if ((av[i] >= '0' && av[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	check_for_valid_args(int ac, char **argv)
{
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0
		|| check_arg_syntax(argv[1]) == 1)
		return (printf("Invalid philosophers numbers\n"), 1);
	if (ft_atoi(argv[2]) <= 0 || check_arg_syntax(argv[2]) == 1)
		return (printf("Invalid time to die\n"), 1);
	if (ft_atoi(argv[3]) <= 0 || check_arg_syntax(argv[3]) == 1)
		return (printf("Invalid time to eat"), 1);
	if (ft_atoi(argv[4]) <= 0 || check_arg_syntax(argv[4]) == 1)
		return (printf("Invalid time to sleep\n"), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_arg_syntax(argv[5]) == 1))
		return (printf("Invalid number of times each\
	philosopher must eat\n"), 1);
	return (0);
}

long	ft_atoi(char *str)
{
	int		i;
	long	signe;
	long	resu;

	i = 0;
	signe = 1;
	resu = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		resu = resu * 10 + (str[i] - 48);
		i++;
	}
	return (resu * signe);
}
