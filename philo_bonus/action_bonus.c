#include "philo_bonus.h"

void	eating(t_philo *philo)
{
	sem_wait(philo->condition->get_forks);
	sem_wait(philo->condition->fork_s);
	print_message(" has taken a left fork\n", philo, 0);
	sem_wait(philo->condition->fork_s);
	print_message(" has taken a right fork\n", philo, 0);
	sem_post(philo->condition->get_forks);
	philo->is_eating = 1;
	sem_wait(philo->eat_dead_s);
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->condition->time_to_die;
	print_message(" is eating\n", philo, 0);
	sem_post(philo->eat_dead_s);
	usleep(philo->condition->time_to_eat * 1000);
	philo->is_eating = 0;
	sem_post(philo->eat_count_s);
}

void	finished_eating(t_philo *philo)
{
	sem_post(philo->condition->fork_s);
	sem_post(philo->condition->fork_s);
	print_message(" is sleeping\n", philo, 0);
	usleep(philo->condition->time_to_sleep * 1000);
}

int	start(t_philo *philo_i)
{
	t_philo		*philo;
	pthread_t	pid;

	philo = (t_philo *)philo_i;
	philo->last_eat = philo->condition->start;
	philo->limit = philo->last_eat + philo->condition->time_to_die;
	if (pthread_create(&pid, NULL, &check_dead, philo_i) != 0)
		return (1);
	pthread_detach(pid);
	while (1)
	{
		eating(philo);
		finished_eating(philo);
		print_message(" is thinking\n", philo, 0);
	}
}

void	made_process(t_condition *condition)
{
	int			i;
	pthread_t	pid;

	i = -1;
	condition->start = get_time();
	if (condition->must_eat != -1)
	{
		pthread_create(&pid, NULL, &check_count, (void *)condition);
		pthread_detach(pid);
	}
	while (++i < condition->philo_num)
	{
		condition->philo[i].pid = fork();
		if (condition->philo[i].pid == 0)
			start(&condition->philo[i]);
		usleep(100);
	}
}
