/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:07:08 by elino             #+#    #+#             */
/*   Updated: 2026/03/06 12:37:14 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	lock_forks(t_philo *p, int first, int second)
{
	pthread_mutex_lock(&p->data->forks[first]);
	if (has_someone_died(p->data))
	{
		pthread_mutex_unlock(&p->data->forks[first]);
		return (0);
	}
	print_action(p, "has taken a fork");
	pthread_mutex_lock(&p->data->forks[second]);
	if (has_someone_died(p->data))
	{
		pthread_mutex_unlock(&p->data->forks[second]);
		pthread_mutex_unlock(&p->data->forks[first]);
		return (0);
	}
	print_action(p, "has taken a fork");
	return (1);
}

static int	take_forks(t_philo *p)
{
	if (p->data->num_philos == 1)
	{
		pthread_mutex_lock(&p->data->forks[p->left_fork]);
		print_action(p, "has taken a fork");
		while (!has_someone_died(p->data))
			usleep(100);
		pthread_mutex_unlock(&p->data->forks[p->left_fork]);
		return (0);
	}
	if (p->id % 2 == 0)
		return (lock_forks(p, p->right_fork, p->left_fork));
	return (lock_forks(p, p->left_fork, p->right_fork));
}

static void	eat(t_philo *p)
{
	print_action(p, "is eating");
	pthread_mutex_lock(&p->data->meal_mutex);
	p->last_meal = get_time();
	p->meals_eaten++;
	pthread_mutex_unlock(&p->data->meal_mutex);
	precise_sleep(p->data->time_to_eat);
}

static void	sleep_think(t_philo *p)
{
	print_action(p, "is sleeping");
	precise_sleep(p->data->time_to_sleep);
	print_action(p, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		usleep(1000);
	while (!has_someone_died(p->data) && !philo_finished(p))
	{
		if (!take_forks(p))
			break ;
		eat(p);
		pthread_mutex_unlock(&p->data->forks[p->left_fork]);
		pthread_mutex_unlock(&p->data->forks[p->right_fork]);
		if (has_someone_died(p->data))
			break ;
		sleep_think(p);
	}
	return (NULL);
}
