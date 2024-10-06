/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:11:42 by ehafiane          #+#    #+#             */
/*   Updated: 2024/10/06 15:25:17 by ehafiane         ###   ########.fr       */
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
	table->num_of_meals = -1;
	if (ac == 6)
		table->num_of_meals = ft_atoi(av[5]);
	table->full = 0;
}



void	print(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->print);
    // printf("tiemstart %llu\n", philo->table->time_start);
	printf("%llu %d	%s\n", get_current_time() - philo->table->time_start, philo->id, msg);
    pthread_mutex_lock(&philo->dead);
	if (philo->table->dead == 1)
    {
        pthread_mutex_unlock(&philo->dead);
	    pthread_mutex_unlock(philo->print);
		return ;
    }
    pthread_mutex_unlock(&philo->dead);
	pthread_mutex_unlock(philo->print);
}

int    isDead(t_philo *philo)
{
    pthread_mutex_lock(&philo->dead);
    if (philo->table->dead == 1)
    {
        pthread_mutex_unlock(&philo->dead);
        return 1;
    }
    pthread_mutex_unlock(&philo->dead);
    return 0;
}

void *routine(void *philo)
{
    t_philo *ph = (t_philo *)philo;
    
    if (ph->id % 2 == 0)
        ft_msleep(ph->table->time_to_eat / 2);
    
    while (1)
    {
        // Take forks
        pthread_mutex_lock(&ph->forks);
        print("has taken a fork", ph);
        pthread_mutex_lock(&ph->next->forks);
        print("has taken a fork", ph);

        // Eat
        pthread_mutex_lock(&ph->eat);
        ph->last_meal_time = get_current_time();
        ph->num_of_meals++;
        pthread_mutex_unlock(&ph->eat);
        print("is eating", ph);
        ft_msleep(ph->table->time_to_eat);

		// Release forks
        pthread_mutex_unlock(&ph->next->forks);
        pthread_mutex_unlock(&ph->forks);

        // Sleep and think
        print("is sleeping", ph);
        ft_msleep(ph->table->time_to_sleep);
        print("is thinking", ph);
        pthread_mutex_lock(&ph->eat);
        if (isDead(ph) || (ph->table->num_of_meals > 0 && ph->num_of_meals >= ph->table->num_of_meals))
        {
            pthread_mutex_unlock(&ph->eat);
            break;
        }
        pthread_mutex_unlock(&ph->eat);
    }
    return NULL;
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



void check_if_died(t_philo *philo_ptr)
{
    t_philo *philo = philo_ptr;
    int i, all_ate;

    while (1)
    {
        i = 0;
        all_ate = (philo->table->num_of_meals > 0);
        while (i < philo->table->nb_philos)
        {
            pthread_mutex_lock(&philo->eat);
            if ((get_current_time() - philo->last_meal_time) >= philo->table->time_to_die)
            {
                pthread_mutex_unlock(&philo->eat);
                pthread_mutex_lock(&philo->dead);
                philo->table->dead = 1;
                pthread_mutex_unlock(&philo->dead);
                print("died", philo);
                return;
            }
            if (philo->table->num_of_meals > 0 && philo->num_of_meals < philo->table->num_of_meals)
                all_ate = 0;
            pthread_mutex_unlock(&philo->eat);
            philo = philo->next;
            i++;
        }
        if (all_ate && philo->table->num_of_meals > 0)
        {
            pthread_mutex_lock(&philo->dead);
            philo->table->dead = 1; 
            pthread_mutex_unlock(&philo->dead);
            return;
        }
    }
}


int main(int ac, char **av)
{
    t_table table;
    t_philo *philo;

    if (!check_nb_arg(ac))
        return (write(2, "Error: wrong number of arguments\n", 34), 1);
    if (check_for_valid_args(ac, av) == 1)
        return (1);
    init_content(&table, av, ac);
    create_philo_node(&table, &philo);
    create_philo_thread(&table, philo);
    check_if_died(philo);

    // while (table.nb_philos--)
    // {
    //     pthread_mutex_destroy(&philo->forks);
    //     pthread_mutex_destroy(&philo->eat);
    //     philo = philo->next;
    // }
    // pthread_mutex_destroy(philo->print);
    // free(philo->print);
	// t_philo *temp;
    // int i = 0;
    // while (i < table.nb_philos)
    // {
    //     temp = philo->next;
    //     free(philo);
    //     philo = temp;
    //     i++;
    // }
    return (0);
}
