/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 20:07:56 by rtrant            #+#    #+#             */
/*   Updated: 2021/04/25 15:19:22 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

extern sem_t	*g_forks_sem;
extern sem_t	*g_write_sem;
extern sem_t	*g_status_sem;

void		init_config(t_philo_config **conf, int argc, char **argv)
{
	(*conf)->ph_count = ft_atoi(argv[1]);
	(*conf)->time_to_die = ft_atoi(argv[2]);
	(*conf)->time_to_eat = ft_atoi(argv[3]);
	(*conf)->time_to_sleep = ft_atoi(argv[4]);
	if (argc > 5)
		(*conf)->num_to_eat = ft_atoi(argv[5]);
	else
		(*conf)->num_to_eat = -1;
}

t_philo		*new_philo(t_philo_config *conf, int i)
{
	t_philo	*philo;

	if (!(philo = malloc(sizeof(t_philo))))
		return (NULL);
	philo->n = i;
	philo->ph_count = conf->ph_count;
	philo->time_to_die = conf->time_to_die;
	philo->time_to_eat = conf->time_to_eat;
	philo->time_to_sleep = conf->time_to_sleep;
	philo->num_ate = 0;
	philo->num_to_eat = conf->num_to_eat;
	philo->start_state = i % 2;
	philo->left_fork = 0;
	philo->right_fork = 0;
	return (philo);
}

int			init_semaphores(t_philo_config *conf)
{
	if ((g_status_sem =
		sem_open("g_status_sem", O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
		return (0);
	if ((g_write_sem =
			sem_open("g_write_sem", O_CREAT | O_EXCL, 0644, 1)) == SEM_FAILED)
	{
		sem_close(g_status_sem);
		return (0);
	}
	if ((g_forks_sem = sem_open("g_forks_sem", O_CREAT | O_EXCL,
							0644, conf->ph_count)) == SEM_FAILED)
	{
		sem_close(g_status_sem);
		sem_close(g_write_sem);
		return (0);
	}
	return (1);
}

int			malloc_all(t_philo_config *conf, pthread_t **threads,
						t_philo ***philos)
{
	if (!(*threads = malloc(sizeof(pthread_t) * conf->ph_count)))
		return (0);
	if (!(*philos = malloc(sizeof(t_philo *) * conf->ph_count)))
		return (0);
	return (1);
}
