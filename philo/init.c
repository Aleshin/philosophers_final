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

void	input(t_philo *philo, char **argv)
{
	philo->num_of_philos = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->num_meals = ft_atoi(argv[5]);
	else
		philo->num_meals = -1;
}

void	set_philosophers(t_philo *philo, t_data *set)
{
	size_t	start_time;
	int		i;

	i = 0;
	start_time = get_current_time();
	set->dead_flag = 0;
	set->finished_philo_counter = 0;
	while (i < philo->num_of_philos)
	{
		set->philos[i].philo_id = i + 1;
		set->philos[i].eating = 0;
		set->philos[i].meals_counter = 0;
		set->philos[i].flag_all_ate = 0;
		set->philos[i].last_meal = start_time;
		set->philos[i].start_time = start_time;
		set->philos[i].num_of_philos = philo->num_of_philos;
		set->philos[i].time_to_die = philo->time_to_die;
		set->philos[i].time_to_eat = philo->time_to_eat;
		set->philos[i].time_to_sleep = philo->time_to_sleep;
		set->philos[i].num_meals = philo->num_meals;
		set->philos[i].end_flag = &set->dead_flag;
		set->philos[i].data = set;
		i++;
	}
}

int	init_mutexes(t_data *set, t_philo *philo)
{
	int	i;

	i = 0;
	set->philos = malloc(philo->num_of_philos * sizeof(t_philo));
	if (!set->philos)
		return (0);
	pthread_mutex_init(&set->write_lock, NULL);
	pthread_mutex_init(&set->meal_lock, NULL);
	pthread_mutex_init(&set->dead_lock, NULL);
	while (i < philo->num_of_philos)
	{
		pthread_mutex_init(&set->philos[i].l_fork, NULL);
		set->philos[i].end_flag = &set->dead_flag;
		i++;
	}
	i = 0;
	while (i < philo->num_of_philos)
	{
		set->philos[i].r_fork
			= set->philos[(i + 1) % philo->num_of_philos].l_fork;
		i++;
	}
	return (1);
}

void	cleanup_all(t_data *set)
{
	int	i;

	i = 0;
	while (i < set->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&set->philos[i].l_fork);
		i++;
	}
	pthread_mutex_destroy(&set->meal_lock);
	pthread_mutex_destroy(&set->dead_lock);
	pthread_mutex_destroy(&set->write_lock);
	free(set->philos);
}
