/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread_sems.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 18:54:55 by rtrant            #+#    #+#             */
/*   Updated: 2021/04/24 15:29:09 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

extern sem_t	*g_status_sem;
extern sem_t	*g_forks_sem;
extern sem_t	*g_write_sem;

int			init_thread_semaphores(void)
{
	if ((g_status_sem =
		sem_open("g_status_sem", O_CREAT)) == SEM_FAILED)
		return (0);
	if ((g_write_sem = sem_open("g_write_sem", O_CREAT)) == SEM_FAILED)
	{
		sem_close(g_status_sem);
		return (0);
	}
	if ((g_forks_sem =
		sem_open("g_forks_sem", O_CREAT)) == SEM_FAILED)
	{
		sem_close(g_status_sem);
		sem_close(g_write_sem);
		return (0);
	}
	return (1);
}
