/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:11:42 by ehafiane          #+#    #+#             */
/*   Updated: 2024/10/01 01:47:27 by ehafiane         ###   ########.fr       */
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
	table->time_start = get_current_time();
	table->num_of_meals = -1;
	if (ac == 6)
		table->num_of_meals = ft_atoi(av[5]);
	table->full = 0;
}

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	if (ph->id % 2 == 0)
		ft_usleep(400);
	while (1)
	{
		pthread_mutex_lock(&ph->forks);
		printf("%ld %d has taken a fork\n", get_current_time() - ph->table->time_start, ph->id);
		pthread_mutex_lock(&ph->forks);
		printf("%ld %d has taken a fork\n", get_current_time() - ph->table->time_start, ph->id);
		printf("%ld %d is eating\n", get_current_time() - ph->table->time_start, ph->id);
		ft_usleep(ph->table->time_to_eat);
		pthread_mutex_unlock(&ph->forks);
		pthread_mutex_unlock(&ph->forks);
		printf("%ld %d is sleeping\n", get_current_time() - ph->table->time_start, ph->id);
		ft_usleep(ph->table->time_to_sleep);
		printf("%ld %d is thinking\n", get_current_time() - ph->table->time_start, ph->id);
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
	// create_philo_thread(&table, philo);
}