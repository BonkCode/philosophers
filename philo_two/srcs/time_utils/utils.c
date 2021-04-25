/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:51:11 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/14 20:06:18 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void			start_timer(double *time_start)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	*time_start = 1000 * tv.tv_sec + tv.tv_usec / 1000;
}

double			get_time_since(double time_start)
{
	struct timeval	tv;
	double			current_time;

	gettimeofday(&tv, NULL);
	current_time = 1000 * tv.tv_sec + tv.tv_usec / 1000;
	return (current_time - time_start);
}

__useconds_t	ms_to_microseconds(double ms)
{
	return (ms * 1000);
}
