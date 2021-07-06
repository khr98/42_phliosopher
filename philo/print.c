/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyerkim <hyerkim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:30:48 by hyerkim           #+#    #+#             */
/*   Updated: 2021/07/06 21:00:33 by hyerkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
