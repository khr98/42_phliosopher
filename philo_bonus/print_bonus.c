#include "philo_bonus.h"

void	print_error(char *s)
{
	printf("%s\n", s);
	exit(0);
}

void	print_message(char *s, t_philo *philo, int is_dead)
{
	int		time;

	sem_wait(philo->condition->message_s);
	time = get_time();
	time -= philo->condition->start;
	printf("%dms %d %s", time, philo->index, s);
	if (!is_dead)
		sem_post(philo->condition->message_s);
}
