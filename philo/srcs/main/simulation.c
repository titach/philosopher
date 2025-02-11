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

void ft_usleep(long milliseconds)
{
	long start = current_milliseconds();

	while ((current_milliseconds() - start) < milliseconds)
		usleep(100);
}

int	dying(t_philo *philo)
{
	if (philo->table->end == false)
		return (1);
	pthread_mutex_lock(&philo->table->print);
	long	t_cur = current_milliseconds() - philo->table->time_start;
	long	n_cur = philo->next_eat / 1000;
	// printf(BCYN"%ld\t%d is checked[%ld]\n"reset, t_cur, philo->id, philo->next_eat / 1000);
	pthread_mutex_unlock(&philo->table->print);
	if (t_cur > n_cur)
	{
		pthread_mutex_lock(&philo->table->print);
		printf(BRED"%ld\t%d died\n"reset, philo->table->t_die / 1000 + 1, philo->id);
		pthread_mutex_unlock(&philo->table->print);
		// pthread_mutex_lock(&philo->table->lock);
		philo->table->end = false;
		// pthread_mutex_unlock(&philo->table->lock);
		return (1);
	}
	return (0);
}

int	thinking(t_philo *philo)
{
	int	check;

	pthread_mutex_lock(&philo->table->lock);
	check = dying(philo);
	pthread_mutex_unlock(&philo->table->lock);
	if (check == 1)
		return (1);
	pthread_mutex_lock(&philo->table->print);
	printf(GRN"%ld\t%d is thinking\n"reset, current_milliseconds() - philo->table->time_start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	return (0);
}

int	sleeping(t_philo *philo)
{
	int	check;

	pthread_mutex_lock(&philo->table->lock);
	check = dying(philo);
	pthread_mutex_unlock(&philo->table->lock);
	if (check == 1)
		return (1);
	pthread_mutex_lock(&philo->table->print);
	printf(BLU"%ld\t%d is sleeping\n"reset, current_milliseconds() - philo->table->time_start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	ft_usleep(philo->table->t_sleep / 1000);
	return (0);
}

int	take_forks(t_philo *philo, int first, int second)
{
	int	check;

	pthread_mutex_lock(&philo->table->fork[first]);
	pthread_mutex_lock(&philo->table->fork[second]);
	pthread_mutex_lock(&philo->table->lock);
	check = dying(philo);
	pthread_mutex_unlock(&philo->table->lock);
	if (check == 1)
	{
		pthread_mutex_unlock(&philo->table->fork[first]);
		pthread_mutex_unlock(&philo->table->fork[second]);
		return (1);
	}
	pthread_mutex_lock(&philo->table->print);
	printf("%ld\t%d has taken a fork\n", current_milliseconds() - philo->table->time_start, philo->id);
	printf("%ld\t%d has taken a fork\n", current_milliseconds() - philo->table->time_start, philo->id);
	pthread_mutex_unlock(&philo->table->print);
	return (0);
}

void	leave_fork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->fork[philo->fist_fork]);
	pthread_mutex_unlock(&philo->table->fork[philo->sec_fork]);
}

void	print_eating(t_philo *philo, int id, char *status)
{
	pthread_mutex_lock(&philo->table->print);
	philo->last_eat = current_milliseconds() - philo->table->time_start;
	printf(YEL"%ld\t%d %s[before %ld][%d meals]\n"reset, philo->last_eat, id, status, philo->next_eat / 1000, philo->count_meals + 1);
	philo->count_meals++;
	pthread_mutex_unlock(&philo->table->print);
	ft_usleep(philo->table->t_eat / 1000);
	
}

int	eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		usleep(100); // id เลขคู่จับช้ากว่า
		if (take_forks(philo, philo->fist_fork, philo->sec_fork) == 1)
			return (1);
		// pthread_mutex_lock(&philo->table->monitor);
		// dying(philo);
		// pthread_mutex_unlock(&philo->table->monitor);
	}
	else
	{
		if (take_forks(philo, philo->sec_fork, philo->fist_fork) == 1)
			return (1);
		// dying(philo);
	}
	// philo->last_eat = current_milliseconds() - philo->table->time_start;
	print_eating(philo, philo->id, "is eating");
	// philo->last_eat = philo->last_eat + philo->table->t_eat / 1000;
	// philo->next_eat = (philo->last_eat * 1000) + philo->table->t_die; 
	philo->next_eat = (philo->last_eat * 1000) + philo->table->t_die; 
	// philo->count_meals++;
	leave_fork(philo);
	usleep(100);
	return (0);
}

void    *dining_room(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->table->monitor);
	if (philo->table->time_start == 0) // ให้ตั้งค่าแค่ครั้งเดียว
		philo->table->time_start = current_milliseconds();
	pthread_mutex_unlock(&philo->table->monitor);
	// int i = -1;//ใส่monitor เช็คใน while ด้วย (philo->table->end)
	while (1)
	{
		philo->next_eat = (philo->last_eat * 1000) + philo->table->t_die; 
		// pthread_mutex_lock(&philo->table->print);
		// printf("[THREAD %d] %ld + %ld = %ld\n", philo->id, philo->last_eat, philo->table->t_die, philo->next_eat);
		// pthread_mutex_unlock(&philo->table->print);
	/*eat*/
		if (eating(philo) == 1)
			return (NULL);// break
		// pthread_mutex_lock(&philo->table->monitor);
		// dying(philo);
		// pthread_mutex_unlock(&philo->table->monitor);
	/*sleep*/
		if (sleeping(philo) == 1)
			return (NULL);// break
	/*think*/
		if (thinking(philo) == 1)
			return (NULL);// break
	}
	
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
