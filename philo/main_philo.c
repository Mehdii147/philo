/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:11:42 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/29 16:22:00 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
   	if (!check_nb_arg(ac))
		return (write(2, "Error: wrong number of arguments\n", 34), 1);
    if (check_for_valid_args(ac, av) == 1)
        return (1);
}