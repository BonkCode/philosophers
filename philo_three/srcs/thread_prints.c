/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_prints.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:44:48 by rtrant            #+#    #+#             */
/*   Updated: 2021/04/25 15:23:28 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

extern double	g_start_time;
extern sem_t	*g_write_sem;
extern sem_t	*g_status_sem;
extern int		g_status;

void	thread_putstr_fd(char *s, int fd)
{
	sem_wait(g_status_sem);
	sem_wait(g_write_sem);
	ft_putstr_fd(s, fd);
	sem_post(g_write_sem);
	sem_post(g_status_sem);
}

void	thread_putnbr_fd(int n, int fd)
{
	sem_wait(g_status_sem);
	sem_wait(g_write_sem);
	ft_putnbr_fd(n, fd);
	sem_post(g_write_sem);
	sem_post(g_status_sem);
}

void	thread_print(char *msg, int n)
{
	sem_wait(g_status_sem);
	sem_wait(g_write_sem);
	ft_putnbr_fd(get_time_since(g_start_time), 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(n, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
	sem_post(g_write_sem);
	sem_post(g_status_sem);
}
