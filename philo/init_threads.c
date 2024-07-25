/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <saleshin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:14:49 by saleshin          #+#    #+#             */
/*   Updated: 2024/07/14 23:15:01 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread,
				NULL, routine, &data->philos[i]))
		{
			write(2, "Error thread create\n", 20);
			cleanup_all(data);
			return (0);
		}
		i++;
	}
	return (1);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL))
		{
			write(2, "Error thread join\n", 18);
			cleanup_all(data);
			return (0);
		}
		i++;
	}
	return (1);
}

int	create_and_join_threads(t_data *data)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor, data))
	{
		write(2, "Error monitor thread create\n", 28);
		cleanup_all(data);
		return (0);
	}
	if (!create_threads(data))
		return (0);
	if (!join_threads(data))
		return (0);
	if (pthread_join(monitor_thread, NULL))
	{
		write(2, "Error monitor thread join\n", 26);
		cleanup_all(data);
		return (0);
	}
	return (1);
}
