/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:11:47 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/30 23:42:59 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_table
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_of_meals;
	size_t			time_start;
	int				dead;
	int				full;
	struct s_philo	*philo;
}	t_table;

typedef struct s_philo
{
	size_t			last_meal_time;
	int				id;
	int				num_of_meals;
	pthread_mutex_t	forks;
	pthread_t		philo;
	t_table			*table;
	struct s_philo	*next;
}	t_philo;

//main functions
void			*routine(void *philo);
size_t			get_current_time(void);
int				ft_usleep(size_t milliseconds);
void			init_content(t_table *table, char **av, int ac);
void			ft_lstaddback(t_philo **philo, t_philo *new);
t_philo			*ft_lstnew(t_table *philo, int id);
void			create_philo_node(t_table *table, t_philo **philo);
void			create_philo_thread(t_table *table, t_philo *philo);

//parsing_philo.c
int				check_for_valid_args(int ac, char **argv);
int				check_arg_syntax(char *av);
int				check_nb_arg(int ac);
int				check_over_flow(char **av);
//utils.c
long long int	ft_atoll(char *str);
int				ft_atoi(char *str);

#endif