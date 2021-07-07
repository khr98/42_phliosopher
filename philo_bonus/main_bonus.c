/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:45:46 by hyerkim           #+#    #+#             */
/*   Updated: 2021/07/06 21:37:44 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		kill(condition->philo[i].pid, SIGKILL);
		sem_close(condition->philo[i].eat_count_s);
		sem_close(condition->philo[i].eat_dead_s);
	}
	free(condition->philo);
	sem_close(condition->fork_s);
	sem_close(condition->exit_s);
	sem_close(condition->message_s);
}

int	main(int argc, char *argv[])
{
	t_condition	condition;

	if (argc < 5 || argc > 6)
		print_error("wrong variables!");
	else
	{
		if (check_argv(argv))
			print_error("invaild argv!");
		if (init_condition(&condition, argv))
			print_error("init error!");
		made_process(&condition);
	}
	sem_wait(condition.exit_s);
	sem_post(condition.exit_s);
	free_all(&condition);
	return (0);
}
