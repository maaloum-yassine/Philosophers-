/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utl1_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:47:42 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/05/29 01:01:45 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_strlen(char *str)
{
	int	lenght;

	lenght = 0;
	while (str[lenght])
		lenght++;
	return (lenght);
}

static void	ft_semaphore_initializing(t_data **s_data)
{
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/last_eat");
	(*s_data)->fork = sem_open("/fork", O_CREAT,
			0600, (*s_data)->number_process);
	(*s_data)->print = sem_open("/print", O_CREAT, 0600, 1);
	(*s_data)->last_eat = sem_open("/last_eat", O_CREAT, 0600, 1);
}

static int	ft_initialize_philo(t_philo **s_philo, t_data **s_data)
{
	int	index;

	index = -1;
	(*s_philo) = malloc(sizeof(t_philo) * (*s_data)->number_process);
	if (!(*s_philo))
		return (0);
	(*s_data)->array_id_process = malloc(sizeof(int)
			* (*s_data)->number_process);
	if (!(*s_data)->array_id_process)
		return (0);
	while (++index < (*s_data)->number_process)
	{
		(*s_philo)[index].id = index + 1;
		(*s_philo)[index].time_last_eat = ft_get_time();
		(*s_philo)[index].count_eat = 0;
		(*s_philo)[index].ptr_data = *s_data;
	}
	ft_semaphore_initializing(s_data);
	return (1);
}

int	ft_initialize_data(int ac, char **av, t_philo **s_philo, t_data **s_data)
{
	*s_data = malloc(sizeof(t_data));
	if (!s_data)
		return (0);
	(*s_data)->number_process = ft_atoi(av[1]);
	(*s_data)->time_to_die = ft_atoi(av[2]);
	(*s_data)->time_to_eat = ft_atoi(av[3]);
	(*s_data)->time_to_sleep = ft_atoi(av[4]);
	(*s_data)->time_to_start = ft_get_time();
	(*s_data)->array_id_process = NULL;
	if (ac == 6 && ft_atoi(av[5]) > 0)
		(*s_data)->number_eat = ft_atoi(av[5]);
	else
		(*s_data)->number_eat = -1;
	if (ft_initialize_philo(s_philo, s_data) == 0)
	{
		ft_free(*s_philo, *s_data);
		return (0);
	}
	return (1);
}
