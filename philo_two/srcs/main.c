/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:37:09 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/14 20:14:42 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"
#include <stdio.h>

double			g_start_time;
sem_t			*g_forks_sem;
sem_t			*g_write_sem;
sem_t			*g_status_sem;
int				g_num_full;
int				g_status;

int		validate_input(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	if (ft_atoi(argv[1]) <= 1)
		return (0);
	if (argc == 6 && ft_atoi(argv[5]) < 0)
		return (0);
	return (1);
}

void	create_philos(t_philo_config *conf, pthread_t **threads,
						t_philo ***philos)
{
	int	i;

	i = -1;
	while (++i < conf->ph_count)
	{
		if (!((*philos)[i] = new_philo(conf, i)))
			continue ;
		pthread_create(&((*threads)[i]), NULL, &run_philo, (*philos)[i]);
	}
}

int		main(int argc, char **argv)
{
	t_philo_config	*conf;
	pthread_t		*threads;
	t_philo			**philos;

	threads = NULL;
	philos = NULL;
	g_num_full = 0;
	sem_unlink("g_status_sem");
	sem_unlink("g_write_sem");
	sem_unlink("g_forks_sem");
	if (!(conf = malloc(sizeof(t_philo_config))))
		return (1);
	init_config(&conf, argc, argv);
	if ((!validate_input(argc, argv)) ||
		(!malloc_all(conf, &threads, &philos)) ||
		(!init_semaphores(conf)))
		return (free_all(&conf, &threads, &philos));
	start_timer(&g_start_time);
	create_philos(conf, &threads, &philos);
	join_all_threads(conf, &threads);
	destroy_all_semaphores();
	free_all(&conf, &threads, &philos);
	return (0);
}
