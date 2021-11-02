#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

typedef struct s_philo
{
	int					index;
	int					is_eating;
	int					limit;
	int					last_eat;
	int					lfork;
	int					rfork;
	pid_t				pid;
	struct s_condition	*condition;
	sem_t				*eat_dead_s;
	sem_t				*eat_count_s;
}						t_philo;

typedef struct s_condition
{
	int			philo_num;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_eat;
	int			start;
	t_philo		*philo;
	sem_t		*fork_s;
	sem_t		*message_s;
	sem_t		*exit_s;
	sem_t		*check_dead_s;
	sem_t		*get_forks;
}				t_condition;

int				init_sem(t_condition *condition);
void			init_philo(t_condition *condition);
int				init_condition(t_condition *condition, char **argv);

int				ft_atoi(const char *str);
int				ft_strlen(char *s);
int				ft_isdigit(char *str);
int				get_time(void);

void			eating(t_philo *philo);
void			finished_eating(t_philo *philo);
int				start(t_philo *philo_i);
void			made_process(t_condition *condition);

void			print_error(char *s);
void			print_message(char *s, t_philo *philo, int is_dead);

void			*check_dead(void *philo_v);
void			*check_count(void *condition);
int				check_argv(char **argv);

#endif
