/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:36:49 by elino             #+#    #+#             */
/*   Updated: 2026/03/06 10:07:55 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	mutex_locker(t_philo *p, int *finished, long *last_meal)
{
	pthread_mutex_lock(&p->data->death_mutex);
	if (p->data->someone_died)
	{
		pthread_mutex_unlock(&p->data->death_mutex);
		return ;
	}
	pthread_mutex_unlock(&p->data->death_mutex);
	pthread_mutex_lock(&p->data->meal_mutex);
	*last_meal = p->last_meal;
	*finished = p->finished;
	pthread_mutex_unlock(&p->data->meal_mutex);
}

static int	check_death(t_philo *p)
{
	long	now;
	long	last_meal;
	int		finished;

	mutex_locker(p, &finished, &last_meal);
	if (finished)
		return (0);
	now = get_time();
	if (now - last_meal > p->data->time_to_die)
	{
		pthread_mutex_lock(&p->data->death_mutex);
		if (p->data->someone_died)
		{
			pthread_mutex_unlock(&p->data->death_mutex);
			return (0);
		}
		p->data->someone_died = 1;
		pthread_mutex_unlock(&p->data->death_mutex);
		pthread_mutex_lock(&p->data->print_mutex);
		printf("%ld %d died\n", get_time() - p->data->start_time, p->id);
		pthread_mutex_unlock(&p->data->print_mutex);
		return (1);
	}
	return (0);
}

static int	check_finished(t_philo *p)
{
	int	done;

	if (p->data->num_times_to_eat <= 0)
		return (0);
	pthread_mutex_lock(&p->data->meal_mutex);
	done = (!p->finished
			&& p->meals_eaten >= p->data->num_times_to_eat);
	if (done)
	{
		p->finished = 1;
		p->data->finished_philos++;
	}
	pthread_mutex_unlock(&p->data->meal_mutex);
	return (done);
}

static int	all_finished(t_data *data)
{
	int	done;

	if (data->num_times_to_eat <= 0)
		return (0);
	pthread_mutex_lock(&data->meal_mutex);
	done = (data->finished_philos == data->num_philos);
	pthread_mutex_unlock(&data->meal_mutex);
	if (done)
	{
		pthread_mutex_lock(&data->death_mutex);
		data->someone_died = 1;
		pthread_mutex_unlock(&data->death_mutex);
	}
	return (done);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	while (1)
	{
		i = 0;
		while (i < philos[0].data->num_philos)
		{
			if (check_death(&philos[i]))
				return (NULL);
			check_finished(&philos[i]);
			i++;
		}
		if (all_finished(philos[0].data))
			return (NULL);
		usleep(1000);
	}
}
