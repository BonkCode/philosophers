/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtrant <rtrant@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 09:49:52 by rtrant            #+#    #+#             */
/*   Updated: 2021/04/25 15:13:50 by rtrant           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>

typedef struct	s_philo_config
{
	int		ph_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_to_eat;
}				t_philo_config;

typedef struct	s_philo
{
	int		n;
	int		ph_count;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		num_to_eat;
	int		num_ate;
	int		start_state;
	int		left_fork;
	int		right_fork;
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
void			*run_philo(void *data);
void			handle_fullness(t_philo *philo);
void			lock_left_fork(t_philo *philo);
void			lock_right_fork(t_philo *philo);
void			unlock_left_fork(t_philo *philo);
void			unlock_right_fork(t_philo *philo);
int				init_thread_semaphores(void);
int				malloc_all(t_philo_config *conf, pthread_t **threads,
							t_philo ***philos);
int				init_semaphores(t_philo_config *conf);
t_philo			*new_philo(t_philo_config *conf, int i);
void			init_config(t_philo_config **conf, int argc, char **argv);
void			join_all_threads(t_philo_config *conf, pthread_t **threads);
void			destroy_all_semaphores(void);
int				free_all(t_philo_config **conf, pthread_t **threads,
						t_philo ***philos);
void			*die(t_philo *philo);
void			wait_full_philos(t_philo_config *conf, pid_t **children);
int				abort_philo_creation(t_philo ***philos,
					pid_t **children, int i);
void			waid_dead_philos(t_philo_config *conf, pid_t **children);
void			handle_processes(int pid, t_philo *philo,
					pid_t **children, t_philo_config *conf);

#endif
