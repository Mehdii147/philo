/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:19:26 by ehafiane          #+#    #+#             */
/*   Updated: 2024/10/07 13:20:42 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print(char *job, t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	printf("%zu	%d %s\n", current_var(philo->current), philo->id, job);
	pthread_mutex_unlock(philo->print);
}

void	*routin(void *str)
{
	t_philo	*philo;

	philo = (t_philo *)str;
	while (1)
	{
		pthread_mutex_lock(&(philo->fork));
		print("has taken a fork", philo);
		pthread_mutex_lock(&(philo->next->fork));
		print("has taken a fork", philo);
		pthread_mutex_lock(&(philo)->eat);
		philo->last_meal = get_current_time();
		philo->num_meals++;
		pthread_mutex_unlock(&(philo)->eat);
		print("is eating", philo);
		ft_msleep(philo, philo->time_to_eat);
		pthread_mutex_unlock(&(philo->next->fork));
		pthread_mutex_unlock(&(philo->fork));
		if (philo->max_nb_meals && philo->max_nb_meals < philo->num_meals)
			break ;
		print("is sleeping", philo);
		ft_msleep(philo, philo->time_to_sleep);
		print("is thinking", philo);
	}
	return (NULL);
}

void	if_died(t_philo *philo)
{
	while (1)
	{
		if (philo->max_nb_meals && check_eating(philo))
			break ;
		pthread_mutex_lock(&(philo)->eat);
		if (philo->time_to_die <= get_current_time() - philo->last_meal)
		{
			pthread_mutex_lock(philo->print);
			printf("%zu	%d died\n", current_var(philo->current), philo->id);
			pthread_mutex_unlock(&(philo)->eat);
			return ;
		}
		pthread_mutex_unlock(&(philo)->eat);
		usleep(500);
		philo = philo->next;
	}
}

void	create_philos(t_philo *philo)
{
	pthread_mutex_t	*print;
	int				i;

	i = -1;
	print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(print, NULL);
	while (++i < philo->nb_philo)
	{
		philo->print = print;
		philo->current = get_current_time();
		philo->last_meal = get_current_time();
		pthread_mutex_init(&(philo->fork), NULL);
		pthread_mutex_init(&(philo->eat), NULL);
		philo = philo->next;
	}
	i = 0;
	while (i < philo->nb_philo)
	{
		pthread_create(&(philo)->philos, NULL, &routin, philo);
		usleep(50);
		pthread_detach(philo->philos);
		philo = philo->next;
		i++;
	}
	if_died(philo);
}

int	main(int ac, char **av)
{
	int		i;
	int		nb_philos;
	t_philo	*philo;

	i = 0;
	if (check_nb_arg(ac) == 0)
		return (printf("Error: wrong number of arguments"), 1);
	philo = NULL;
	nb_philos = ft_atoi(av[1]);
	if (check_for_valid_args(ac, av))
		return (1);
	fill_nodes(&philo, nb_philos, ac, av);
	ft_lstlast(philo)->next = philo;
	create_philos(philo);
	return (0);
}
