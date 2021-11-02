#include "philo.h"

int	get_time(void)
{
	struct timeval	time;
	int				ms;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (ms);
}

void	free_all(t_condition *condition)
{
	int	i;

	i = -1;
	while (++i < condition->philo_num)
	{
		pthread_mutex_destroy(&condition->fork_m[i]);
		pthread_mutex_destroy(&condition->philo[i].eat_count_m);
		pthread_mutex_destroy(&condition->philo[i].mutex);
	}
	free(condition->fork_m);
	free(condition->philo);
	pthread_mutex_destroy(&condition->exit_m);
	pthread_mutex_destroy(&condition->message_m);
}

int	main(int argc, char *argv[])
{
	t_condition	condition;

	if (argc < 5 || argc > 6)
	{
		printf("wrong variables!\n");
		return (0);
	}
	else
	{
		if (check_argv(argv))
		{
			printf("invaild argv!\n");
			return (0);
		}
		if (init_condition(&condition, argv))
		{
			printf("init error!\n");
			return (0);
		}
		made_threads(&condition);
	}
	pthread_mutex_lock(&condition.exit_m);
	pthread_mutex_unlock(&condition.exit_m);
	free_all(&condition);
	return (0);
}
