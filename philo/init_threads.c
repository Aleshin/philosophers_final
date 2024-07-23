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

int	create_threads(t_philo *data, t_program *set)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_create(&set->philos[i].thread,
				NULL, routine, &set->philos[i]))
		{
			ft_putstr_fd("Error thread create", 2);
			cleanup_all(set);
			return (0);
		}
		i++;
	}
	return (1);
}

int	join_threads(t_philo *data, t_program *set)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (pthread_join(set->philos[i].thread, NULL))
		{
			ft_putstr_fd("Error thread join", 2);
			cleanup_all(set);
			return (0);
		}
		i++;
	}
	return (1);
}

int	create_and_join_threads(t_philo *data, t_program *set)
{
	pthread_t	monitor_thread;

	if (pthread_create(&monitor_thread, NULL, monitor, set))
	{
		ft_putstr_fd("Error monitor thread create", 2);
		cleanup_all(set);
		return (0);
	}
	if (!create_threads(data, set))
		return (0);
	if (!join_threads(data, set))
		return (0);
	if (pthread_join(monitor_thread, NULL))
	{
		ft_putstr_fd("Error monitor thread join", 2);
		cleanup_all(set);
		return (0);
	}
	return (1);
}
