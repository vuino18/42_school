/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 15:38:25 by elino             #+#    #+#             */
/*   Updated: 2026/03/06 12:36:17 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_finished(t_philo *p)
{
	int	finished;

	pthread_mutex_lock(&p->data->meal_mutex);
	finished = (p->data->num_times_to_eat > 0
			&& p->meals_eaten >= p->data->num_times_to_eat);
	pthread_mutex_unlock(&p->data->meal_mutex);
	return (finished);
}

void	print_action(t_philo *p, char *msg)
{
	long	time;

	if (has_someone_died(p->data))
		return ;
	pthread_mutex_lock(&p->data->print_mutex);
	if (has_someone_died(p->data))
	{
		pthread_mutex_unlock(&p->data->print_mutex);
		return ;
	}
	time = get_time() - p->data->start_time;
	printf("%ld %d %s\n", time, p->id, msg);
	pthread_mutex_unlock(&p->data->print_mutex);
}

int	has_someone_died(t_data *data)
{
	int	ret;

	pthread_mutex_lock(&data->death_mutex);
	ret = data->someone_died;
	pthread_mutex_unlock(&data->death_mutex);
	return (ret);
}

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	long	n;

	n = 0;
	if (!str)
		return (0);
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str)
	{
		if (!is_digit(*str))
			return (0);
		n = n * 10 + (*str - '0');
		str++;
	}
	return ((int)n);
}
