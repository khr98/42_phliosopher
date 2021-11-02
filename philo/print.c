#include "philo.h"

void	print_message(char *s, t_philo *philo, int is_dead)
{
	int		time;

	pthread_mutex_lock(&philo->condition->message_m);
	time = get_time();
	time -= philo->condition->start;
	printf("%dms %d %s", time, philo->index, s);
	if (!is_dead)
		pthread_mutex_unlock(&philo->condition->message_m);
}
