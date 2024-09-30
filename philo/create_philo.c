/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:11:44 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/30 17:52:07 by ehafiane         ###   ########.fr       */
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

void	init_content(t_philo *t, char **av, int ac)
{
	int	i;

	i = 0;
	t->num_of_philos = ft_atoi(av[1]);
	t->time_to_die = ft_atoi(av[2]);
	t->time_to_eat = ft_atoi(av[3]);
	t->time_to_sleep = ft_atoi(av[4]);
	t->dead = 0;
	t->time = ft_get_time();
	t->num_times_to_eat = -1;
	if (ac == 6)
		t->num_times_to_eat = ft_atoi(av[5]);
	t->max_ate = 0;
}

void	ft_lstaddback(t_philo **philo, t_philo *new)
{
	t_philo	*tmp;

	tmp = *philo;
	if (!*philo)
	{
		*philo = new;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_philo	*ft_lstnew(t_philo *philo, int id)
{
	t_philo	*p;

	p = malloc(sizeof(t_philo));
	if (!p)
		return (NULL);
	p->meals_eaten = 0;
	p->id = id + 1;
	p->last_meal = philo->time;
	p->next = philo;
	p->next = NULL;
	return (p);
}