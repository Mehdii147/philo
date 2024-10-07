/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:48:44 by ehafiane          #+#    #+#             */
/*   Updated: 2024/10/07 13:21:26 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eating(t_philo *philo)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < philo->nb_philo)
	{
		pthread_mutex_lock(&philo->eat);
		if (philo->num_meals >= philo->max_nb_meals)
			count++;
		pthread_mutex_unlock(&philo->eat);
		philo = philo->next;
		i++;
	}
	if (count == philo->nb_philo)
		return (1);
	return (0);
}

int	ft_msleep(t_philo *philo, size_t t_todo)
{
	size_t	time;

	time = current_var(philo->current);
	while (1)
	{
		if (current_var(philo->current) - time >= t_todo)
			return (1);
		usleep(500);
	}
	return (0);
}
