/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:20:05 by elino             #+#    #+#             */
/*   Updated: 2026/03/06 09:12:47 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->num_philos);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->meal_mutex, NULL);
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->num_times_to_eat = ft_atoi(argv[5]);
		if (data->num_times_to_eat <= 0)
			return (0);
	}
	else
		data->num_times_to_eat = -1;
	data->someone_died = 0;
	data->finished_philos = 0;
	if (data->num_philos <= 0)
		return (0);
	if (data->time_to_die <= 0)
		return (0);
	if (data->time_to_eat <= 0)
		return (0);
	if (data->time_to_sleep <= 0)
		return (0);
	return (init_mutexes(data));
}

static void	set_philo(t_philo *p, t_data *data, int i)
{
	p->id = i + 1;
	p->left_fork = i;
	p->right_fork = (i + 1) % data->num_philos;
	p->last_meal = get_time();
	p->meals_eaten = 0;
	p->finished = 0;
	p->data = data;
	pthread_mutex_init(&p->meal_mutex, NULL);
}

int	init_philos(t_philo **philos, t_data *data)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!*philos)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		set_philo(&(*philos)[i], data, i);
		i++;
	}
	data->philos = *philos;
	return (1);
}
