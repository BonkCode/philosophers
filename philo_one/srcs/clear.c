/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 20:11:18 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/14 20:12:14 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

extern pthread_mutex_t	*g_forks;

void	join_all_threads(t_philo_config *conf, pthread_t **threads)
{
	int	i;

	i = -1;
	while (++i < conf->ph_count)
		pthread_join((*threads)[i], NULL);
}

void	destroy_all_mutexes(t_philo_config *conf)
{
	int	i;

	i = -1;
	while (++i < conf->ph_count)
		pthread_mutex_destroy(&(g_forks[i]));
}

int		free_all(t_philo_config **conf, pthread_t **threads, t_philo ***philos)
{
	int	i;

	if (*threads)
		free(*threads);
	if (g_forks)
		free(g_forks);
	i = -1;
	while (++i < (*conf)->ph_count)
	{
		if (*philos)
			free((*philos)[i]);
	}
	if (*conf)
		free(*conf);
	if (*philos)
		free(*philos);
	return (1);
}
