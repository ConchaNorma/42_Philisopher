/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:08:12 by cnorma            #+#    #+#             */
/*   Updated: 2022/01/16 18:56:06 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_data
{
	int				philos_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_to_eat;
	long			start_time;
	long			start_eat;
	int				philo_id;
	pthread_t		thread;
	pid_t			*pid;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*finish;
	int				death_status;
}				t_data;

int		ft_atoi_short(const char *str);
long	get_ms(void);
int		check_arg(int argc, char **arg);
void	wait_time(int wait_time);
void	free_data(t_data *data);
int		init_sem(t_data *data);
int		init_data(t_data *data, char **arg);
void	ph_sleeping(t_data *data);
void	ph_eating(t_data *data);
void	*child_create(void *arg);
void	*death_check(void *arg);
int		simulation(t_data *data);
void	wait_finish(t_data *data);

#endif
