/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 01:40:49 by tchaloei          #+#    #+#             */
/*   Updated: 2025/02/10 18:46:52 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    one_philosopher(t_table *table)
{
	table->time_start = current_milliseconds();
	printf("%ld\t1 has taken a fork\n", current_milliseconds() - table->time_start);
	usleep(table->t_die);
	printf(BRED"%ld\t1 died\n"reset, table->t_die / 1000 + 1);
}
