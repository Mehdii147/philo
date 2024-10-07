/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ehafiane <ehafiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:58:47 by ehafiane          #+#    #+#             */
/*   Updated: 2024/10/07 13:21:49 by ehafiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int					id;
	int					nb_philo;
	size_t				last_meal;
	size_t				current;
	pthread_mutex_t		fork;
	pthread_mutex_t		*print;
	pthread_mutex_t		eat;
	int					num_meals;
	int					max_nb_meals;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	pthread_t			philos;
	struct s_philo		*next;
}						t_philo;

int				check_for_valid_args(int ac, char **argv);
void			fill_nodes(t_philo **philo, int nb_philos, int ac, char **av);
t_philo			*ft_lstlast(t_philo *lst);
t_philo			*ft_lstnew(int ac, char **av);
void			ft_lstadd_front(t_philo **lst, t_philo *new);
void			ft_lstadd_back(t_philo **lst, t_philo *new);
size_t			current_var(size_t var);
size_t			get_current_time(void);
void			init_content(t_philo *philo, int ac, char **av);
int				ft_msleep(t_philo *philo, size_t t_todo);
int				check_eating(t_philo *philo);
int				parsing(char **av);
long			ft_atoi(char *str);
void			if_died(t_philo *philo);
int				check_nb_arg(int ac);

#endif
