/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_prints.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 11:44:48 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/14 19:53:22 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

extern double			g_start_time;
extern pthread_mutex_t	g_write_mutex;
extern int				g_status;

void	thread_putstr_fd(char *s, int fd)
{
	pthread_mutex_lock(&g_write_mutex);
	ft_putstr_fd(s, fd);
	pthread_mutex_unlock(&g_write_mutex);
}

void	thread_putnbr_fd(int n, int fd)
{
	pthread_mutex_lock(&g_write_mutex);
	ft_putnbr_fd(n, fd);
	pthread_mutex_unlock(&g_write_mutex);
}

void	thread_print(char *msg, int n)
{
	pthread_mutex_lock(&g_write_mutex);
	if (g_status)
	{
		pthread_mutex_unlock(&g_write_mutex);
		return ;
	}
	ft_putnbr_fd(g_status, 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(get_time_since(g_start_time), 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd(n, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
	pthread_mutex_unlock(&g_write_mutex);
}
