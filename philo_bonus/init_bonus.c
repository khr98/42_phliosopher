/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:45:44 by hyerkim           #+#    #+#             */
/*   Updated: 2021/07/06 20:45:44 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_sem(t_condition *condition)
{
	sem_unlink("forks");
	sem_unlink("write");
	sem_unlink("check_dead");
	sem_unlink("get_forks");
	sem_unlink("exit");
	condition->fork_s = sem_open("forks", O_CREAT, 0644, condition->philo_num);
	condition->message_s = sem_open("write", O_CREAT, 0644, 1);
	condition->check_dead_s = sem_open("check_dead", O_CREAT, 0644, 1);
	condition->get_forks = sem_open("get_forks", O_CREAT, 0644, 1);
	condition->exit_s = sem_open("exit", O_CREAT, 0644, 1);
	sem_wait(condition->exit_s);
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
		condition->philo[i].condition = condition;
		sem_unlink("eat_dead");
		sem_unlink("eat_count");
		condition->philo[i].eat_dead_s = sem_open("eat_dead",
				O_CREAT, 0644, 1);
		condition->philo[i].eat_count_s = sem_open("eat_count",
				O_CREAT, 0644, 1);
		sem_wait(condition->philo[i].eat_count_s);
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
		condition->must_eat = 0;
	condition->start = get_time();
	condition->philo = NULL;
	condition->fork_s = NULL;
	condition->philo = (t_philo *)malloc(sizeof(t_philo)
			* condition->philo_num);
	if (!condition->philo)
		return (1);
	init_philo(condition);
	if (init_sem(condition))
		return (1);
	return (0);
}
