/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 20:07:56 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/14 20:10:41 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

extern pthread_mutex_t	*g_forks;
extern pthread_mutex_t	g_write_mutex;
extern pthread_mutex_t	g_status_mutex;

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
	return (philo);
}

int			init_mutexes(t_philo_config *conf)
{
	int	i;
	int	j;

	i = -1;
	if ((pthread_mutex_init(&g_status_mutex, NULL)))
		return (0);
	if ((pthread_mutex_init(&g_write_mutex, NULL)))
	{
		pthread_mutex_destroy(&g_status_mutex);
		return (0);
	}
	while (++i < conf->ph_count)
	{
		if ((pthread_mutex_init(&(g_forks[i]), NULL)))
		{
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&(g_forks[j]));
			pthread_mutex_destroy(&g_status_mutex);
			pthread_mutex_destroy(&g_write_mutex);
			return (0);
		}
	}
	return (1);
}

int			malloc_all(t_philo_config *conf, pthread_t **threads,
						t_philo ***philos)
{
	if (!(*threads = malloc(sizeof(pthread_t) * conf->ph_count)))
		return (0);
	if (!(g_forks = malloc(sizeof(pthread_mutex_t) * conf->ph_count)))
		return (0);
	if (!(*philos = malloc(sizeof(t_philo *) * conf->ph_count)))
		return (0);
	return (1);
}
