/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:08:12 by cnorma            #+#    #+#             */
/*   Updated: 2022/01/06 15:34:01 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>

typedef struct s_input
{
	int			philos_num;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			must_to_eat;
}				t_input;

typedef struct s_philo
{
	int				philo_id;
	t_input			*input;
	struct s_data	*data;
	pthread_mutex_t	*fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*print;
	int				ph_must_to_eat;
	long			start_eat;
}				t_philo;

typedef struct s_data
{
	long			start_time;
	t_philo			*philo;
	t_input			*input;
	pthread_t		*thread;
	pthread_mutex_t	**forks;
	int				death_status;
	int				finish_eat_flag;
}				t_data;

int		ft_atoi_short(const char *str);
long	get_ms(void);
int		check_arg(int argc, char **arg);
void	wait_time(int wait_time);
void	free_data(t_data *data);
int		init_forks(t_data *data);
int		init_philos(t_data *data);
int		init_data(t_data *data, char **arg);
void	ph_sleeping(t_philo *philo);
void	eat_counting(t_philo *philo);
void	ph_eating(t_philo *philo);
void	*thread_create(void *arg);
void	simulation(t_data *data);

#endif
