/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:45:41 by hyerkim           #+#    #+#             */
/*   Updated: 2021/07/06 21:05:42 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_dead(void *philo_v)
{
	t_philo	*philo;
	int		time;

	philo = (t_philo *)philo_v;
	while (1)
	{
		sem_wait(philo->condition->check_dead_s);
		sem_wait(philo->eat_dead_s);
		time = get_time();
		if (!philo->is_eating && (time > philo->limit))
		{
			print_message(" died\n", philo, 1);
			sem_post(philo->eat_dead_s);
			sem_post(philo->condition->exit_s);
			return (NULL);
		}
		sem_post(philo->eat_dead_s);
		sem_post(philo->condition->check_dead_s);
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
			sem_wait(condition->philo[i].eat_count_s);
			i++;
		}
		count++;
	}
	print_message(" all finished eating\n", &condition->philo[0], 1);
	sem_post(condition->exit_s);
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
