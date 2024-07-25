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

int	check_input(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc >= 5 && argc <= 6)
	{
		while (i < argc)
		{
			if (ft_atoi(argv[i]) == 0)
			{
				write(2, "wrong argument\n", 15);
				return (0);
			}
			i++;
		}
	}
	else
	{
		write(2, "Wrong # of arguments\n", 21);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philo		philo;
	t_data		data;

	if (!check_input(argc, argv))
		return (1);
	input(&data, argv);
	set_philosophers(&philo, &data);
	if (!init_mutexes(&data, &philo))
	{
		printf("Error init mutexes\n");
		return (1);
	}
	if (!create_and_join_threads(&data))
	{
		printf("Error create and join threads\n");
		return (1);
	}
	cleanup_all(&data);
	return (0);
}
