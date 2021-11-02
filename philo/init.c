#include "philo.h"

int	init_mutex(t_condition *condition)
{
	int	i;

	pthread_mutex_init(&condition->message_m, NULL);
	pthread_mutex_init(&condition->check_dead_m, NULL);
	pthread_mutex_init(&condition->exit_m, NULL);
	pthread_mutex_lock(&condition->exit_m);
	condition->fork_m = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* condition->philo_num);
	if (!condition->fork_m)
		return (1);
	i = -1;
	while (++i < condition->philo_num)
		pthread_mutex_init(&condition->fork_m[i], NULL);
	return (0);
}

void	init_philo(t_condition *condition)
{
	int	i;

	i = 0;
	while (i < condition->philo_num)
	{
		condition->philo[i].index = i + 1;
		condition->philo[i].is_eating = 0;
		condition->philo[i].rfork = (i + 1) % condition->philo_num;
		condition->philo[i].lfork = i;
		condition->philo[i].condition = condition;
		pthread_mutex_init(&condition->philo[i].mutex, NULL);
		pthread_mutex_init(&condition->philo[i].eat_count_m, NULL);
		pthread_mutex_lock(&condition->philo[i].eat_count_m);
		i++;
	}
}

int	init_condition(t_condition *condition, char **argv)
{
	condition->philo_num = ft_atoi(argv[1]);
	condition->time_to_die = ft_atoi(argv[2]);
	condition->time_to_eat = ft_atoi(argv[3]);
	condition->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		condition->must_eat = ft_atoi(argv[5]);
	else
		condition->must_eat = -1;
	condition->start = get_time();
	condition->philo = NULL;
	condition->fork_m = NULL;
	condition->philo = (t_philo *)malloc(sizeof(t_philo)
			* condition->philo_num);
	if (!condition->philo)
		return (1);
	init_philo(condition);
	if (init_mutex(condition))
		return (1);
	return (0);
}
