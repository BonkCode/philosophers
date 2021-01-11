/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:37:09 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/11 13:45:10 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"
#include <stdio.h>

double			g_start_time;
pthread_mutex_t	*g_forks;
pthread_mutex_t	g_write_mutex;
pthread_mutex_t	g_status_mutex;
int				g_status;

int	validate_input(int argc, char **argv)
{
	return (1); // todo
}

void	*die(t_philo *philo)
{
	pthread_mutex_lock(&g_status_mutex);
	if (!g_status)
		thread_print("dead", philo->n);
	g_status = 1;
	pthread_mutex_unlock(&g_status_mutex);
	return (NULL);
}

void	*eat(double *last_eaten, t_philo *philo)
{
	double	time_not_eaten;

	time_not_eaten = get_time_since(*last_eaten);
	if (time_not_eaten > philo->time_to_die || g_status)
		return (die(philo));
	pthread_mutex_lock(&(g_forks[philo->n]));
	time_not_eaten = get_time_since(*last_eaten);
	if (time_not_eaten > philo->time_to_die || g_status)
	{
		pthread_mutex_unlock(&(g_forks[philo->n]));
		return (die(philo));
	}
	thread_print("grabbed fork", philo->n);
	pthread_mutex_lock(&(g_forks[philo->n == (philo->ph_count - 1) ? 0 : philo->n + 1]));
	time_not_eaten = get_time_since(*last_eaten);
	if (time_not_eaten > philo->time_to_die || g_status)
	{
		pthread_mutex_unlock(&(g_forks[philo->n]));
		pthread_mutex_unlock(&(g_forks[philo->n == (philo->ph_count - 1) ? 0 : philo->n + 1]));
		return (die(philo));
	}
	thread_print("eating", philo->n);
	usleep(ms_to_microseconds(philo->time_to_eat));
	time_not_eaten = 0;
	if (time_not_eaten > philo->time_to_die || g_status)
	{
		pthread_mutex_unlock(&(g_forks[philo->n]));
		pthread_mutex_unlock(&(g_forks[philo->n == (philo->ph_count - 1) ? 0 : philo->n + 1]));
		return (die(philo));
	}
	start_timer(last_eaten);
	pthread_mutex_unlock(&(g_forks[philo->n]));
	pthread_mutex_unlock(&(g_forks[philo->n == (philo->ph_count - 1) ? 0 : philo->n + 1]));
	p_sleep(last_eaten, philo);
	return (NULL);
}

void	*think(double *last_eaten, t_philo *philo)
{
	double	time_not_eaten;

	if (g_status)
		return (NULL);
	time_not_eaten = get_time_since(*last_eaten);
	if (time_not_eaten > philo->time_to_die || g_status)
		return (die(philo));
	thread_print("thinking", philo->n);
	eat(last_eaten, philo);
	return (NULL);
}

void	*p_sleep(double *last_eaten, t_philo *philo)
{
	double	time_not_eaten;

	if (g_status)
		return (NULL);
	time_not_eaten = get_time_since(*last_eaten);
	if (time_not_eaten > philo->time_to_die || g_status)
		return (die(philo));
	thread_print("sleeping", philo->n);
	if (time_not_eaten > philo->time_to_die || g_status)
		return (die(philo));
	usleep(ms_to_microseconds(philo->time_to_sleep));
	think(last_eaten, philo);
	return (NULL);
}

void	*run_philo(void *data)
{
	t_philo	*philo;
	double			time_not_eaten;
	double			last_eaten;

	philo = (t_philo *)data;
	start_timer(&last_eaten);
	time_not_eaten = 0;
	time_not_eaten = get_time_since(last_eaten);
	if (philo->n % 3 == 0)
		eat(&last_eaten, philo);
	else if (philo->n % 3 == 1)
		p_sleep(&last_eaten, philo);
	else
		think(&last_eaten, philo);
	ft_putstr_fd("Z", 1);
	return (NULL);
}

void	init_config(t_philo_config **conf, int argc, char **argv)
{
	(*conf)->ph_count = ft_atoi(argv[1]);
	(*conf)->time_to_die = ft_atoi(argv[2]);
	(*conf)->time_to_eat = ft_atoi(argv[3]);
	(*conf)->time_to_sleep = ft_atoi(argv[4]);
}

t_philo	*new_philo(t_philo_config *conf, int i)
{
	t_philo	*philo;
	
	philo = malloc(sizeof(t_philo));
	philo->n = i;
	philo->ph_count = conf->ph_count;
	philo->time_to_die = conf->time_to_die;
	philo->time_to_eat = conf->time_to_eat;
	philo->time_to_sleep = conf->time_to_sleep;
	philo->start_state = i % 2;
	return (philo);
}

int	main(int argc, char **argv)
{
	t_philo_config	*conf;
	pthread_t		*threads;
	t_philo			**philos;
	pthread_t		test;
	int				i;

	conf = malloc(sizeof(t_philo_config));
	if (!validate_input(argc, argv))
		return (-1);
	init_config(&conf, argc, argv);
	if (!(threads = malloc(sizeof(pthread_t) * conf->ph_count)))
		return (1);
	if (!(g_forks = malloc(sizeof(pthread_mutex_t) * conf->ph_count)))
		return (1);
	if (!(philos = malloc(sizeof(t_philo *) * conf->ph_count)))
		return (1);
	i = -1;
	pthread_mutex_init(&g_status_mutex, NULL);
	pthread_mutex_init(&g_write_mutex, NULL);
	while (++i < conf->ph_count)
	{
		pthread_mutex_init(&(g_forks[i]), NULL);
	}
	start_timer(&g_start_time);
	i = -1;
	while (++i < conf->ph_count)
	{
		philos[i] = new_philo(conf, i);
		pthread_create(&(threads[i]), NULL, run_philo, philos[i]);
	}
	i = -1;
	while (++i < conf->ph_count)
	{
		pthread_join(threads[i], NULL);
		ft_putstr_fd("Q", 1);
	}
	ft_putstr_fd("ASDSAD", 1);
	i = -1;
	while (++i < conf->ph_count)
	{
		pthread_mutex_destroy(&(g_forks[i]));
	}
	pthread_mutex_destroy(&g_write_mutex);
	free(threads);
	free(g_forks);
	i = -1;
	while (++i < conf->ph_count)
		free(philos[i]);
	free(conf);
	free(philos);
	return (0);
}
