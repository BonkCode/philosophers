/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 20:04:10 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/14 20:07:19 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

extern int				g_num_full;
extern int				g_status;
extern pthread_mutex_t	*g_forks;
extern pthread_mutex_t	g_status_mutex;

void	lock_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&(g_forks[philo->n]));
}

void	lock_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&(g_forks[philo->n == (philo->ph_count - 1) ?
						0 : philo->n + 1]));
}

void	unlock_left_fork(t_philo *philo)
{
	pthread_mutex_unlock(&(g_forks[philo->n]));
}

void	unlock_right_fork(t_philo *philo)
{
	pthread_mutex_unlock(&(g_forks[philo->n == (philo->ph_count - 1) ?
						0 : philo->n + 1]));
}

void	handle_fullness(t_philo *philo)
{
	if (philo->num_ate < philo->num_to_eat &&
		philo->num_ate + 1 >= philo->num_to_eat)
		++g_num_full;
	++philo->num_ate;
	if (g_num_full >= philo->ph_count && philo->num_to_eat > 0)
	{
		pthread_mutex_lock(&g_status_mutex);
		g_status = 1;
		pthread_mutex_unlock(&g_status_mutex);
	}
}
