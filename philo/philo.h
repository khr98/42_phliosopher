/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:30:43 by hyerkim           #+#    #+#             */
/*   Updated: 2021/07/06 21:09:25 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>

typedef struct s_philo
{
	int					index;
	int					is_eating;
	int					limit;
	int					last_eat;
	pthread_t			pid;
	int					lfork;
	int					rfork;
	int					how_many_eat;
	struct s_condition	*condition;
	pthread_mutex_t		mutex;
	pthread_mutex_t		eat_count_m;
}						t_philo;

typedef struct s_condition
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat;
	int				start;
	t_philo			*philo;
	pthread_mutex_t	*fork_m;
	pthread_mutex_t	message_m;
	pthread_mutex_t	exit_m;
	pthread_mutex_t	check_dead_m;
}					t_condition;

int				init_mutex(t_condition *condition);
void			init_philo(t_condition *condition);
int				init_condition(t_condition *condition, char **argv);

int				ft_atoi(const char *str);
int				ft_strlen(char *s);
int				ft_isdigit(char *str);

int				get_time(void);

void			eating(t_philo *philo);
void			finished_eating(t_philo *philo);
void			*start(void *philo_i);
void			made_threads(t_condition *condition);

void			print_message(char *s, t_philo *philo, int is_dead);

void			*check_dead(void *philo_v);
void			*check_count(void *philo_v);
int				check_argv(char **argv);

#endif