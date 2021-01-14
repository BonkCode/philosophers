/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_in_thread.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 20:02:24 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/14 20:14:27 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

extern int				g_status;
extern pthread_mutex_t	g_status_mutex;
extern pthread_mutex_t	*g_forks;

void	*run_philo(void *data)
{
	t_philo	*philo;
	double	last_eaten;

	philo = (t_philo *)data;
	start_timer(&last_eaten);
	if (philo->n % 3 == 0)
		eat(&last_eaten, philo);
	else if (philo->n % 3 == 1)
		p_sleep(&last_eaten, philo);
	else
		think(&last_eaten, philo);
	return (NULL);
}

void	*p_sleep(double *last_eaten, t_philo *philo)
{
	double	time_not_eaten;

	if (g_status)
		return (NULL);
	time_not_eaten = get_time_since(*last_eaten);
	if (time_not_eaten > philo->time_to_die || g_status)
		return (die(philo));
	thread_print("sleeping", philo->n);
	if (time_not_eaten > philo->time_to_die || g_status)
		return (die(philo));
	usleep(ms_to_microseconds(philo->time_to_sleep));
	think(last_eaten, philo);
	return (NULL);
}

void	*think(double *last_eaten, t_philo *philo)
{
	double	time_not_eaten;

	if (g_status)
		return (NULL);
	time_not_eaten = get_time_since(*last_eaten);
	if (time_not_eaten > philo->time_to_die || g_status)
		return (die(philo));
	thread_print("thinking", philo->n);
	eat(last_eaten, philo);
	return (NULL);
}

void	*eat(double *last_eaten, t_philo *philo)
{
	double	time_not_eaten;

	time_not_eaten = get_time_since(*last_eaten);
	if (time_not_eaten > philo->time_to_die || g_status)
		return (die(philo));
	lock_left_fork(philo);
	time_not_eaten = get_time_since(*last_eaten);
	if (time_not_eaten > philo->time_to_die || g_status)
		return (die(philo));
	thread_print("grabbed fork", philo->n);
	lock_right_fork(philo);
	time_not_eaten = get_time_since(*last_eaten);
	if (time_not_eaten > philo->time_to_die || g_status)
		return (die(philo));
	thread_print("eating", philo->n);
	usleep(ms_to_microseconds(philo->time_to_eat));
	handle_fullness(philo);
	time_not_eaten = 0;
	if (time_not_eaten > philo->time_to_die || g_status)
		return (die(philo));
	start_timer(last_eaten);
	unlock_left_fork(philo);
	unlock_right_fork(philo);
	p_sleep(last_eaten, philo);
	return (NULL);
}

void	*die(t_philo *philo)
{
	pthread_mutex_lock(&g_status_mutex);
	if (!g_status)
		thread_print("dead", philo->n);
	g_status = 1;
	pthread_mutex_unlock(&g_status_mutex);
	pthread_mutex_unlock(&(g_forks[philo->n]));
	pthread_mutex_unlock(&(g_forks[philo->n == (philo->ph_count - 1) ?
							0 : philo->n + 1]));
	return (NULL);
}
