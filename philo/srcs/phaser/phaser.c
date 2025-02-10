/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phaser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 23:26:49 by tchaloei          #+#    #+#             */
/*   Updated: 2025/02/05 23:26:49 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_all(t_table *table, int i)
{
	pthread_mutex_destroy(&table->monitor);
	pthread_mutex_destroy(&table->print);
	while (i < table->amount)
	{
		pthread_mutex_destroy(&table->fork[i]);
		i++;
	}
	free(table->fork);
	free(table->philo);
	free(table);
}
