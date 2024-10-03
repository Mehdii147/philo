/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:11:42 by ehafiane          #+#    #+#             */
/*   Updated: 2024/10/03 20:13:44 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_content(t_table *table, char **av, int ac)
{
	table->nb_philos = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->dead = 0;
	table->num_of_meals = 0;
	if (ac == 6)
		table->num_of_meals = ft_atoi(av[5]);
	table->full = 0;
}



void	print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->print);
	// printf("########### time start: %lu\n", philo->table->time_start);
	// printf("########### time now: %lu\n", get_current_time());
	printf("%lu %d	%s\n", get_current_time() - philo->table->time_start, philo->id, msg);
	if (philo->table->dead == 1)
	{
		return ;
	}
	pthread_mutex_unlock(philo->print);
}


void	*routine(void *philo)
{
	t_philo	*ph;
	size_t	start;

	ph = (t_philo *)philo;
	if (ph->id % 2 == 0)
		ft_msleep(ph->table->time_to_sleep);
	pthread_mutex_lock(ph->print);
	int tempDead = ph->table->dead;
	pthread_mutex_unlock(ph->print);
	while (tempDead == 0)
	{
		pthread_mutex_lock(&ph->forks);
		print("has taken a fork", ph);

		pthread_mutex_lock(&ph->next->forks);
		print("has taken a fork", ph);

		pthread_mutex_lock(&(ph)->eat);
		ph->last_meal_time = get_current_time();
		pthread_mutex_unlock(&(ph)->eat);
		print("is eating", ph);
		ft_msleep(ph->table->time_to_eat);
		pthread_mutex_lock(&(ph)->eat);
		ph->num_of_meals++;
		pthread_mutex_unlock(&(ph)->eat);
		pthread_mutex_unlock(&ph->next->forks);
		pthread_mutex_unlock(&ph->forks);
		print("is sleeping", ph);
		ft_msleep(ph->table->time_to_sleep);
		print("is thinking", ph);
		if (ph->table->num_of_meals && ph->num_of_meals >= ph->table->num_of_meals)
		{
			pthread_mutex_lock(ph->print);
			ph->table->full++;
			pthread_mutex_unlock(ph->print);
			break;
		}
		pthread_mutex_lock(ph->print);
		tempDead = ph->table->dead;
		pthread_mutex_unlock(ph->print);
	}
	return (NULL);
}


int	check_eating(t_philo *philo)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while(i < philo->table->nb_philos)
	{
		pthread_mutex_lock(&philo->eat);
		if (philo->num_of_meals >= philo->table->num_of_meals)
			count++;
		pthread_mutex_unlock(&philo->eat);
		philo = philo->next;
		i++;
	}
	if (count == philo->table->nb_philos)
		return (1);
	return (0);
}


void	check_if_died(t_philo *philo_ptr)
{
	t_philo	*philo = philo_ptr;
	int		i;

	while (1)
	{
		i = 0;
		while (i < philo->table->nb_philos)
		{
			pthread_mutex_lock(&philo->eat);
			if ((get_current_time() - philo->last_meal_time) >= philo->table->time_to_die)
			{
				print("died", philo);
				pthread_mutex_lock(philo->print);
				philo->table->dead = 1;
				return ;
			}
			pthread_mutex_unlock(&philo->eat);
			philo = philo->next;
			i++;
		}
		pthread_mutex_lock(philo->print);
		if (check_eating(philo))
			return ;
		pthread_mutex_unlock(philo->print);
	}
}


int main(int ac, char **av)
{
	t_table	table;
	t_philo	*philo;

   	if (!check_nb_arg(ac))
		return (write(2, "Error: wrong number of arguments\n", 34), 1);
    if (check_for_valid_args(ac, av) == 1)
        return (1);
	init_content(&table, av, ac);
	create_philo_node(&table, &philo);
	create_philo_thread(&table, philo);
	check_if_died(philo);
}
