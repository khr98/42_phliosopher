/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:30:21 by hyerkim           #+#    #+#             */
/*   Updated: 2021/07/06 21:11:22 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->condition->fork_m[philo->lfork]);
	print_message(" has taken a left fork\n", philo, 0);
	pthread_mutex_lock(&philo->condition->fork_m[philo->rfork]);
	print_message(" has taken a right fork\n", philo, 0);
	philo->is_eating = 1;
	pthread_mutex_lock(&philo->mutex);
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->condition->time_to_die;
	print_message(" is eating\n", philo, 0);
	pthread_mutex_unlock(&philo->mutex);
	usleep(philo->condition->time_to_eat * 1000);
	philo->how_many_eat++;
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->eat_count_m);
}

void	finished_eating(t_philo *philo)
{
	pthread_mutex_unlock(&philo->condition->fork_m[philo->lfork]);
	pthread_mutex_unlock(&philo->condition->fork_m[philo->rfork]);
	print_message(" has put down  fork\n", philo, 0);
	print_message(" is sleeping\n", philo, 0);
	usleep(philo->condition->time_to_sleep * 1000);
}

void	*start(void *philo_i)
{
	t_philo		*philo;
	pthread_t	pid;

	philo = (void *)philo_i;
	philo->last_eat = get_time();
	philo->limit = philo->last_eat + philo->condition->time_to_die;
	if (pthread_create(&pid, NULL, &check_dead, philo_i) != 0)
		return ((void *)1);
	pthread_detach(pid);
	if (philo->index % 2 != 0)
		usleep(philo->condition->time_to_eat * 500);
	while (1)
	{
		eating(philo);
		finished_eating(philo);
		print_message(" is thinking\n", philo, 0);
	}
}

void	made_threads(t_condition *condition)
{
	int			i;
	pthread_t	pid;

	i = -1;
	condition->start = get_time();
	if (condition->must_eat)
	{
		pthread_create(&pid, NULL, &check_count, (void *)condition);
		pthread_detach(pid);
	}
	while (++i < condition->philo_num)
	{
		pthread_create(&condition->philo[i].pid, NULL,
			&start, &condition->philo[i]);
		pthread_detach(condition->philo[i].pid);
	}
}
