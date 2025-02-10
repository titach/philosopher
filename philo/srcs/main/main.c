/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchaloei <tchaloei@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:28:15 by tchaloei          #+#    #+#             */
/*   Updated: 2025/02/05 18:28:15 by tchaloei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	long	result;
	long	sign;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' && str[i + 1] != '-')
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result *= sign);
}

int	handle_input(t_table *table, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
        free(table);
		write(2, "usage: [num_philo] [t_die] [t_eat] [t_sleep] [option]\n", 54);
		return (1);
	}
	table->amount = ft_atol(av[1]);
	table->t_die = ft_atol(av[2]) * 1000;
	table->t_eat = ft_atol(av[3]) * 1000;
	table->t_sleep = ft_atol(av[4]) * 1000;
	if (table->t_die < 60000 || table->t_eat < 60000 || table->t_sleep < 60000)
	{
        free(table);
		write(2, "timestamp less than 60 ms\n", 26);
		return (1);
	}
	if (av[5])
		table->option = ft_atol(av[5]);
	else
		table->option = -1;
	return (0);
}

int main(int ac, char **av)
{
    t_table *table;

    table = (t_table *)malloc(sizeof(t_table));
    if (handle_input(table, ac, av) == 1)
        return (1);
    //data_init
    phaser_data(table, 0);
    //sim
    start_simulation(table, 0);
    //clean
    clean_all(table, 0);
}
