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

#include "philo_two.h"

extern int		g_num_full;
extern int		g_status;
extern sem_t	*g_forks_sem;
extern sem_t	*g_status_sem;

void	lock_left_fork(t_philo *philo)
{
	sem_wait(g_forks_sem);
	philo->left_fork = 1;
}

void	lock_right_fork(t_philo *philo)
{
	sem_wait(g_forks_sem);
	philo->right_fork = 1;
}

void	unlock_left_fork(t_philo *philo)
{
	sem_post(g_forks_sem);
	philo->left_fork = 0;
}

void	unlock_right_fork(t_philo *philo)
{
	sem_post(g_forks_sem);
	philo->right_fork = 0;
}

void	handle_fullness(t_philo *philo)
{
	if (philo->num_ate < philo->num_to_eat &&
		philo->num_ate + 1 >= philo->num_to_eat)
		++g_num_full;
	++philo->num_ate;
	if (g_num_full >= philo->ph_count && philo->num_to_eat > 0)
	{
		sem_wait(g_status_sem);
		g_status = 1;
		sem_post(g_status_sem);
	}
}
