/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <saleshin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:14:49 by saleshin          #+#    #+#             */
/*   Updated: 2024/07/14 23:15:01 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

//check if this particular philo is dead
static	int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	if (philo->eating == 0 && (get_current_time() - philo->last_meal
			> philo->data->time_to_die))
	{
		pthread_mutex_unlock(&philo->data->meal_lock);
		print_death(philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (0);
}

static	int	check_all_philos(t_data *data)
{
	int	i;

	i = 0;
	if (data->num_of_philos == 1)
	{
		ft_usleep(data->time_to_die);
		print_death(&data->philos[i]);
		return (1);
	}
	while (i < data->num_of_philos)
	{
		if (is_dead(&data->philos[i]))
		{
			pthread_mutex_lock(&data->dead_lock);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

static	int	finish_meal_counter(t_data *program)
{
	int	counter;

	counter = 0;
	pthread_mutex_lock(&program->meal_lock);
	counter = program->finished_philo_counter;
	pthread_mutex_unlock(&program->meal_lock);
	return (counter);
}

static	int	all_ate(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philos)
	{
		if (data->num_meals != -1 && finish_meal_counter(data)
			== data->num_of_philos)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_end_flag(&data->philos[0]))
			return (arg);
		if (all_ate(data) || check_all_philos(data))
		{
			pthread_mutex_lock(&data->dead_lock);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->dead_lock);
			return (arg);
		}
	}
	return (NULL);
}
