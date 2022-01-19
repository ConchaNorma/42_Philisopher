/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:07:05 by cnorma            #+#    #+#             */
/*   Updated: 2022/01/16 18:54:51 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

void	wait_finish(t_data *data)
{
	int	i;

	if (data->must_to_eat > 0)
	{
		i = -1;
		while (++i < data->philos_num)
		{
			waitpid(-1, NULL, WUNTRACED);
			if (data->death_status == 1)
				break ;
		}
	}
	else
		waitpid(-1, NULL, WUNTRACED);
	i = -1;
	while (++i < data->philos_num)
		kill(data->pid[i], SIGTERM);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (check_arg(argc, argv) != 0)
		return (printf("Wrong arguments\n"));
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (printf("Data: malloc error\n"));
	if (init_data(data, argv) != 0)
	{
		free_data(data);
		return (1);
	}
	if (simulation(data) != 0)
		exit(1);
	wait_finish(data);
	free_data(data);
	return (0);
}
