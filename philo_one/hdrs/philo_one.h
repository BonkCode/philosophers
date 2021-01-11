/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:49:52 by rtrant            #+#    #+#             */
/*   Updated: 2021/01/11 12:57:53 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct	s_philo_config
{
	int		ph_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
}				t_philo_config;

typedef struct	s_philo
{
	int		n;
	int		ph_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		start_state;
}				t_philo;

void			start_timer(double *time_start);
double			get_time_since(double time_start);
__useconds_t	ms_to_microseconds(double ms);
int				ft_atoi(const char *nptr);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putchar_fd(char c, int fd);
void			thread_putstr_fd(char *s, int fd);
void			thread_putnbr_fd(int n, int fd);
void			*p_sleep(double *last_eaten, t_philo *philo);
void			*think(double *last_eaten, t_philo *philo);
void			*eat(double *last_eaten, t_philo *philo);
void			thread_print(char *msg, int n);

#endif
