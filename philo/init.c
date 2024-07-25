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

void	input(t_data *data, char **argv)
{
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->num_meals = ft_atoi(argv[5]);
	else
		data->num_meals = -1;
	data->end_flag = 0;
	data->finished_philo_counter = 0;
}

int	set_philosophers(t_philo *philos, t_data *data)
{
	size_t	start_time;
	int		i;

	philos = malloc(data->num_of_philos * sizeof(t_philo));
	if (!philos)
		return (0);
	data->philos = philos;
	start_time = get_current_time();
	i = 0;
	while (i < data->num_of_philos)
	{
		philos[i].philo_id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_counter = 0;
		philos[i].flag_all_ate = 0;
		philos[i].last_meal = start_time;
		philos[i].start_time = start_time;
		philos[i].data = data;
		i++;
	}
	return (0);
}

int	init_mutexes(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	while (i < data->num_of_philos)
		pthread_mutex_init(&philo[i++].l_fork, NULL);
	i = 0;
	while (i < data->num_of_philos)
	{
		philo[i].r_fork
			= philo[(i + 1) % data->num_of_philos].l_fork;
		i++;
	}
	return (1);
}

void	cleanup_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		pthread_mutex_destroy(&data->philos[i].l_fork);
		i++;
	}
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->dead_lock);
	pthread_mutex_destroy(&data->write_lock);
	free(data->philos);
}
