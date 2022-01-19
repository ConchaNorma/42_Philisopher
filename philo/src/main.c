/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cnorma <cnorma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 21:07:05 by cnorma            #+#    #+#             */
/*   Updated: 2022/01/06 15:34:06 by cnorma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (check_arg(argc, argv) != 0)
		return (printf("Wrong arguments\n"));
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (printf("Data: malloc error\n"));
	if (init_data(data, argv) != 0)
	{
		free(data->input);
		free(data);
		return (1);
	}
	simulation(data);
	free_data(data);
	return (0);
}
