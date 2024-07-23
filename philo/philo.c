/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <saleshin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:11:19 by saleshin          #+#    #+#             */
/*   Updated: 2024/07/14 23:11:32 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philo.h"

/*
ARGUMENTS
number_of_philosophers
time_to_die time_to_eat
time_to_sleep
[number_of_times_each_philosopher_must_eat]
*/

int	main(int argc, char **argv)
{
	t_philo		data;
	t_program	set;

	if (!input_ok(argc, argv))
		return (EXIT_FAILURE);
	init_input(&data, argv);
	if (!init_mutexes(&set, &data))
	{
		printf("Error init mutexes\n");
		return (EXIT_FAILURE);
	}
	set_philosophers(&data, &set);
	if (!create_and_join_threads(&data, &set))
	{
		printf("Error create and join threads\n");
		return (EXIT_FAILURE);
	}
	cleanup_all(&set);
	return (0);
}
