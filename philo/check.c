#include "philo.h"

void	*check_dead(void *philo_v)
{
	t_philo	*philo;
	int		time;

	philo = (t_philo *)philo_v;
	while (1)
	{
		pthread_mutex_lock(&philo->condition->check_dead_m);
		pthread_mutex_lock(&philo->mutex);
		time = get_time();
		if (!philo->is_eating && (time > philo->limit))
		{
			print_message(" died\n", philo, 1);
			pthread_mutex_unlock(&philo->mutex);
			pthread_mutex_unlock(&philo->condition->exit_m);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mutex);
		pthread_mutex_unlock(&philo->condition->check_dead_m);
		usleep(1000);
	}
}

void	*check_count(void *condition_v)
{
	t_condition	*condition;
	int			i;
	int			count;

	count = 0;
	condition = (t_condition *)condition_v;
	while (count < condition->must_eat)
	{
		i = 0;
		while (i < condition->philo_num)
		{
			pthread_mutex_lock(&condition->philo[i].eat_count_m);
			i++;
		}
		count++;
	}
	print_message(" all finished eating\n", &condition->philo[0], 1);
	pthread_mutex_unlock(&condition->exit_m);
	return (NULL);
}

int	check_argv(char **argv)
{
	int	i;
	int	len;

	i = 1;
	while (argv[i])
	{
		if (ft_isdigit(argv[i]))
			return (1);
		i++;
	}
	return (0);
}
