/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:45:54 by hyerkim           #+#    #+#             */
/*   Updated: 2021/07/06 21:05:02 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
