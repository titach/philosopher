/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phaser_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 23:38:11 by tchaloei          #+#    #+#             */
/*   Updated: 2025/02/05 23:38:11 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    phaser_data(t_table *table, int i)
{
    table->philo = (t_philo *)malloc(sizeof(t_philo) * table->amount);
    //
    //
    table->fork = (t_mtx *)malloc(sizeof(t_mtx) * table->amount);
    //
    //
    pthread_mutex_init(&table->lock, NULL);
    pthread_mutex_init(&table->monitor, NULL);
    pthread_mutex_init(&table->print, NULL);
    table->end = true;
    while (i < table->amount)
    {
        pthread_mutex_init(&table->fork[i], NULL);
        table->philo[i].id = i + 1;
        table->philo[i].fist_fork = i;
        table->philo[i].sec_fork = (i + 1) % table->amount;
        table->philo[i].count_meals = 0;
        table->philo[i].next_eat = 0;
        table->philo[i].last_eat = 0;
        table->philo[i].life = true;
        table->philo[i].table = table;
        i++;
    }
}
