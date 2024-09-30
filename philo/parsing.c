/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:29:41 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/29 17:44:57 by ehafiane         ###   ########.fr       */
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

int	check_over_flow(char **av)
{
	long long int	ld;
	int				d;
	int				i;

	i = 1;
	while (av[i])
	{
		ld = ft_atoll(av[i]);
		d = ft_atoi(av[i]);
		if (ld != d)
		{
			printf("Error: overflow\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_for_valid_args(int ac, char **argv)
{
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0
		|| check_arg_syntax(argv[1]) == 1)
		return (write(2, "\033[0;31m->\033[0m Invalid philosophers\
			number\n", 39), 1);
	if (ft_atoi(argv[2]) <= 0 || check_arg_syntax(argv[2]) == 1)
		return (write(2, "\033[0;31m->\033[0m Invalid time to die\n", 35), 1);
	if (ft_atoi(argv[3]) <= 0 || check_arg_syntax(argv[3]) == 1)
		return (write(2, "\033[0;31m->\033[0m Invalid time to eat\n", 35), 1);
	if (ft_atoi(argv[4]) <= 0 || check_arg_syntax(argv[4]) == 1)
		return (write(2, "\033[0;31m->\033[0m Invalid time to sleep\n", 37), 1);
	if (argv[5] && (ft_atoi(argv[5]) < 0 || check_arg_syntax(argv[5]) == 1))
		return (write(2, "\033[0;31m->\033[0m Invalid number of times each philosopher\
			must eat\n", 65), 1);
	return (0);
}
