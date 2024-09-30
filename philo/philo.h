/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 10:11:47 by ehafiane          #+#    #+#             */
/*   Updated: 2024/09/30 17:47:21 by ehafiane         ###   ########.fr       */
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

typedef struct s_philo
{
	pthread_t		philo;
	int				id;
	int				meals_eaten;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				dead;
	int				max_ate;
	size_t			last_meal;
	size_t			time;
	pthread_mutex_t	fork;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	struct s_philo	*next;
}					t_philo;

//main functions
size_t			get_current_time(void);

//parsing_philo.c
int				check_for_valid_args(int ac, char **argv);
int				check_arg_syntax(char *av);
int				check_nb_arg(int ac);
int				check_over_flow(char **av);
//utils.c
long long int	ft_atoll(char *str);
int				ft_atoi(char *str);

#endif