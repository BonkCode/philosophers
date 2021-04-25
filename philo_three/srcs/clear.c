/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 20:11:18 by rtrant            #+#    #+#             */
/*   Updated: 2021/04/25 14:26:15 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

extern sem_t	*g_forks_sem;
extern sem_t	*g_write_sem;
extern sem_t	*g_status_sem;
extern sem_t	*g_fullness_sem;

void	join_all_threads(t_philo_config *conf, pthread_t **threads)
{
	int	i;

	i = -1;
	while (++i < conf->ph_count)
		pthread_join((*threads)[i], NULL);
}

void	destroy_all_semaphores(void)
{
	sem_close(g_forks_sem);
	sem_close(g_status_sem);
	sem_close(g_write_sem);
	sem_close(g_fullness_sem);
}

int		free_all(t_philo_config **conf, pthread_t **threads, t_philo ***philos)
{
	int	i;

	if (*threads)
		free(*threads);
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
