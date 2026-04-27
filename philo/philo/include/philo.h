/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elino <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 12:26:30 by elino             #+#    #+#             */
/*   Updated: 2026/03/06 10:00:03 by elino            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_data
{
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
	int				someone_died;
	int				num_philos;
	int				num_times_to_eat;
	int				finished_philos;
	t_philo			*philos;
}	t_data;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	int				finished;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	t_data			*data;
}	t_philo;

int		init_data(t_data *data, int argc, char **argv);
int		ft_atoi(const char *s);
int		philo_finished(t_philo *p);
int		init_philos(t_philo **philos, t_data *data);
int		has_someone_died(t_data *arg);
long	get_time(void);
void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);
void	precise_sleep(long time);
void	print_action(t_philo *philo, char *msg);
void	clean_all(t_data *data, t_philo *philos);

#endif
