/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <saleshin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:14:49 by saleshin          #+#    #+#             */
/*   Updated: 2024/07/14 23:15:01 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

int	check_end_flag(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->end_flag == 1)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

//only prints death, so end flag should be set to 1 before or after
void	print_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write_lock);
	printf("%zu %d died\n", get_current_time()
		- philo->start_time, philo->philo_id);
	pthread_mutex_unlock(&philo->data->write_lock);
}

//print only if end flag is 0
static void	ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(&philo->data->meal_lock);
	safe_print(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

//print only if end flag is 0
static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->l_fork);
	safe_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_current_time();
	philo->eating = 1;
	pthread_mutex_unlock(&philo->data->meal_lock);
	safe_print(philo, "is eating");
	philo->meals_counter++;
	if (philo->data->num_meals != -1
		&& philo->meals_counter == philo->data->num_meals)
	{
		pthread_mutex_lock(&philo->data->meal_lock);
		philo->data->finished_philo_counter++;
		pthread_mutex_unlock(&philo->data->meal_lock);
	}
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->r_fork);
	pthread_mutex_unlock(&philo->l_fork);
}

//function executed in each tread
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 == 0)
		ft_usleep(100);
	if (philo->data->num_of_philos == 1)
	{
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_lock(&philo->data->dead_lock);
		philo->data->end_flag = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (arg);
	}
	while (1)
	{
		if (check_end_flag(philo->data))
			break ;
		eat(philo);
		ft_sleep(philo);
		safe_print(philo, "is thinking");
	}
	return (arg);
}
