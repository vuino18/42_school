/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 11:23:30 by elino             #+#    #+#             */
/*   Updated: 2026/03/06 09:14:55 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	start_threads(t_data *data, t_philo *philos,
		pthread_t *monitor)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&philos[i].thread, NULL,
				philo_routine, &philos[i]))
			return (0);
		i++;
	}
	if (pthread_create(monitor, NULL,
			monitor_routine, philos))
		return (0);
	return (1);
}

static void	wait_threads(t_data *data, t_philo *philos,
		pthread_t monitor)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_philo		*philos;
	pthread_t	monitor;

	if (argc < 5 || argc > 6)
		return (printf("Error\n"), 1);
	if (!init_data (&data, argc, argv))
		return (1);
	if (!init_philos(&philos, &data))
		return (1);
	data.start_time = get_time();
	if (!start_threads(&data, philos, &monitor))
		return (1);
	wait_threads(&data, philos, monitor);
	clean_all(&data, philos);
	return (0);
}
