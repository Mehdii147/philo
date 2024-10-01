/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:11:44 by ehafiane          #+#    #+#             */
/*   Updated: 2024/10/01 01:43:16 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	ft_lstaddback(t_philo **philo, t_philo *new)
{
	t_philo	*tmp;

	if (!*philo)
	{
		*philo = new;
		return ;
	}
	tmp = *philo;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_philo	*ft_lstnew(t_table *table, int id)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->num_of_meals = 0;
	philo->id = id + 1;
	philo->last_meal_time = table->time_start;
	philo->table = table;
	philo->next = NULL;
	return (philo);
}

void	create_philo_node(t_table *table, t_philo **philo)
{
	int		i;
	t_philo	*ph;

	i = 0;
	*philo = NULL;
	while (i < table->nb_philos)
	{
		ph = ft_lstnew(table, i);
		ft_lstaddback(philo, ph);
		i++;
	}
	ph->next = *philo;
}

void	create_philo_thread(t_table *table, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < table->nb_philos)
	{
		pthread_create(&philo->philo, NULL, &routine, philo);
		philo = philo->next;
		i++;
	}
}