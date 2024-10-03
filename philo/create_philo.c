/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:11:44 by ehafiane          #+#    #+#             */
/*   Updated: 2024/10/03 18:19:59 by ehafiane         ###   ########.fr       */
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
	philo->last_meal_time = get_current_time();
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
	pthread_mutex_t		*print;

	i = 0;
	print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(print, NULL);
	philo->table->time_start = get_current_time();
	
	while (i < table->nb_philos)
	{
		philo->print = print;
		philo->last_meal_time = get_current_time();
		pthread_mutex_init(&philo->forks, NULL);
		pthread_mutex_init(&philo->eat, NULL);
		i++;
		philo = philo->next;
	}
	i = 0;
	philo = philo->next;
	while (i < table->nb_philos)
	{
		pthread_create(&philo->philo, NULL, &routine, philo);
		pthread_detach(philo->philo);
		philo = philo->next;
		i++;
	}
}
