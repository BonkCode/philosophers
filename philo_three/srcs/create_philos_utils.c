/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philos_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 14:50:28 by rtrant            #+#    #+#             */
/*   Updated: 2021/04/25 15:13:23 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

extern sem_t	*g_fullness_sem;
extern sem_t	*g_status_sem;

void	wait_full_philos(t_philo_config *conf, pid_t **children)
{
	int j;

	j = -1;
	while (++j < conf->ph_count)
		sem_wait(g_fullness_sem);
	sem_wait(g_status_sem);
	j = -1;
	while (++j < conf->ph_count)
		kill((*children)[j], SIGINT);
}

int		abort_philo_creation(t_philo ***philos, pid_t **children, int i)
{
	int	j;

	j = -1;
	while (++j < i)
	{
		free((*philos)[j]);
		(*philos)[j] = NULL;
	}
	free(*philos);
	philos = NULL;
	free(*children);
	return (-1);
}

void	waid_dead_philos(t_philo_config *conf, pid_t **children)
{
	int	j;

	waitpid(-1, NULL, 0);
	j = -1;
	while (++j < conf->ph_count)
		kill((*children)[j], SIGINT);
}

void	handle_processes(int pid, t_philo *philo,
				pid_t **children, t_philo_config *conf)
{
	if (pid == 0)
	{
		run_philo(philo);
		exit(0);
	}
	else if (conf->num_to_eat >= 0)
		wait_full_philos(conf, children);
	else
		waid_dead_philos(conf, children);
}
