/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 23:57:03 by tchaloei          #+#    #+#             */
/*   Updated: 2025/02/05 23:57:03 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dying(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf(BCYN"%ld\t%d is checked\n"reset, current_milliseconds() - philo->table->time_start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	if (current_milliseconds() - philo->table->time_start > philo->next_eat / 100)
		printf(BRED"%ld\t1 died\n"reset, philo->table->t_die / 1000 + 1);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->print);
	printf("%ld\t%d is sleeping\n", current_milliseconds() - philo->table->time_start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	usleep(philo->table->t_sleep);
}

void	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->monitor);
		dying(philo);
		pthread_mutex_unlock(&philo->table->monitor);
		usleep(100); // philoคู่จับช้ากว่า
		pthread_mutex_lock(&philo->table->fork[philo->fist_fork]);
		pthread_mutex_lock(&philo->table->fork[philo->sec_fork]);
		pthread_mutex_lock(&philo->table->print);
		printf("%ld\t%d has taken a fork\n", current_milliseconds() - philo->table->time_start, philo->id);
		printf("%ld\t%d has taken a fork\n", current_milliseconds() - philo->table->time_start, philo->id);
		philo->last_eat = current_milliseconds() - philo->table->time_start;
		printf("%ld\t%d is eating [before %ld][%d meals]\n", philo->last_eat, philo->id, philo->next_eat / 1000, philo->count_meals + 1);
		philo->count_meals++;
		pthread_mutex_unlock(&philo->table->print);
		usleep(philo->table->t_eat);
		pthread_mutex_unlock(&philo->table->fork[philo->fist_fork]);
		pthread_mutex_unlock(&philo->table->fork[philo->sec_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->monitor);
		dying(philo);
		pthread_mutex_unlock(&philo->table->monitor);
		pthread_mutex_lock(&philo->table->fork[philo->sec_fork]);
		pthread_mutex_lock(&philo->table->fork[philo->fist_fork]);
		pthread_mutex_lock(&philo->table->print);
		printf("%ld\t%d has taken a fork\n", current_milliseconds() - philo->table->time_start, philo->id);
		printf("%ld\t%d has taken a fork\n", current_milliseconds() - philo->table->time_start, philo->id);
		philo->last_eat = current_milliseconds() - philo->table->time_start;
		printf("%ld\t%d is eating [before %ld][%d meals]\n", philo->last_eat, philo->id, philo->next_eat / 1000, philo->count_meals + 1);
		philo->count_meals++;
		pthread_mutex_unlock(&philo->table->print);
		usleep(philo->table->t_eat);
		pthread_mutex_unlock(&philo->table->fork[philo->sec_fork]);
		pthread_mutex_unlock(&philo->table->fork[philo->fist_fork]);
	}
}

void    *dining_room(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->table->monitor);
	if (philo->table->time_start == 0) // ให้ตั้งค่าแค่ครั้งเดียว
    	philo->table->time_start = current_milliseconds();
	pthread_mutex_unlock(&philo->table->monitor);
	philo->next_eat = philo->last_eat + philo->table->t_die;
	/*eat*/
	eating(philo);
	/*sleep*/
	// sleeping(philo);
	/*tjink*/
	// pthread_mutex_lock(&philo->table->print);
	// printf("%ld\t%d is thinking\n", current_milliseconds() - philo->table->time_start, philo->id);
	// pthread_mutex_unlock(&philo->table->print);

	return (NULL);
}

void    start_simulation(t_table *table, int i)
{
	if (table->amount == 0)
		return ;
	else if (table->amount == 1)
		one_philosopher(table);//*TODO
	else
	{
		 while (i < table->amount)
		{
			pthread_create(&table->philo[i].threads, NULL, dining_room, &table->philo[i]);
			i++;
		}
		i = 0;
		while (i < table->amount)
		{
			pthread_join(table->philo[i].threads, NULL);
			i++;
		}
	}
}
