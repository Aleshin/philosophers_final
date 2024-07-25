/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saleshin <saleshin@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 23:14:49 by saleshin          #+#    #+#             */
/*   Updated: 2024/07/14 23:15:01 by saleshin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t			thread;
	int					philo_id;
	int					eating; //1 0
	int					flag_all_ate; //1 0 if meals counter == num_meals
	int					meals_counter; //++
	size_t				last_meal; //start eating + time to eat//shared
	size_t				start_time;
	pthread_mutex_t		r_fork;
	pthread_mutex_t		l_fork;
	struct s_data		*data;
}	t_philo;

typedef struct s_data
{
	int				num_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				num_meals;
	int				end_flag; //shared
	int				finished_philo_counter; //shared
	pthread_mutex_t	dead_lock; //shared
	pthread_mutex_t	meal_lock; //shared
	pthread_mutex_t	write_lock; //shared
	t_philo			*philos; //array of structs type t_philo with all info
}	t_data;

//INIT
void			input(t_data *data, char **argv);
int				set_philosophers(t_philo *data, t_data *set);
int				create_and_join_threads(t_data *data);
int				init_mutexes(t_data *set, t_philo *data);
void			cleanup_all(t_data *set);

//ROUTINE
void			*routine(void *data);
void			*monitor(void *arg);

//UTILS
size_t			get_current_time(void);
unsigned int	ft_atoi(char *str);
void			print_death(t_philo *philo);
int				check_end_flag(t_data *data);
void			safe_print(t_philo *philo, char *str);
int				ft_usleep(size_t milliseconds);

#endif
