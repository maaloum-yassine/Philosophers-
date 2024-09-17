/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 19:31:34 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/05/29 18:23:44 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_strlen(char *str)
{
	int	lenght;

	lenght = 0;
	while (str[lenght])
		lenght++;
	return (lenght);
}

static void	ft_destroy_mutex(t_philo *s_philo, char for_fork, char for_stop)
{
	int	i;

	i = -1;
	if (for_fork == 'y')
	{
		while (++i < s_philo->ptr_data->number_thread)
			pthread_mutex_destroy(&(s_philo->ptr_data->fork[i]));
	}
	if (for_stop == 'y')
	{
		i = -1;
		while (++i < 2)
			pthread_mutex_destroy(&(s_philo->ptr_data->stop[i]));
	}
	ft_usleep(200);
}

void	ft_free(t_philo *s_philo, t_data *s_data, char for_fork, char for_stop)
{
	if (for_fork == 'y')
		ft_destroy_mutex(s_philo, for_fork, for_stop);
	if (s_philo->ptr_data->stop != NULL)
		free (s_philo->ptr_data->stop);
	if (s_philo->ptr_data->fork != NULL)
		free (s_philo->ptr_data->fork);
	if (s_data != NULL)
		free (s_data);
	if (s_philo != NULL)
		free (s_philo);
}

static int	ft_initialize_philo(t_philo **s_philo, t_data **s_data)
{
	int	index;

	(*s_data)->fork = NULL;
	index = -1;
	(*s_philo) = malloc(sizeof(t_philo) * (*s_data)->number_thread);
	if (!(*s_philo))
		return (0);
	(*s_data)->fork = malloc(sizeof(pthread_mutex_t)
			* (*s_data)->number_thread);
	if (!(*s_data)->fork)
		return (0);
	while (++index < (*s_data)->number_thread)
	{
		(*s_philo)[index].id = index + 1;
		(*s_philo)[index].time_last_eat = ft_get_time();
		(*s_philo)[index].count_eat = 0;
		(*s_philo)[index].ptr_data = *s_data;
	}
	(*s_philo)->ptr_data->stop = NULL;
	(*s_philo)->ptr_data->stop = malloc(sizeof(pthread_mutex_t) * 2);
	if (!(*s_philo)->ptr_data->stop)
		return (0);
	return (1);
}

int	ft_initialize_data(int ac, char **av, t_philo **s_philo, t_data **s_data)
{
	*s_data = malloc(sizeof(t_data));
	if (!s_data)
		return (0);
	(*s_data)->number_thread = ft_atoi(av[1]);
	(*s_data)->time_to_die = ft_atoi(av[2]);
	(*s_data)->time_to_eat = ft_atoi(av[3]);
	(*s_data)->time_to_sleep = ft_atoi(av[4]);
	(*s_data)->time_to_start = ft_get_time();
	if (ac == 6 && ft_atoi(av[5]) > 0)
		(*s_data)->number_eat = ft_atoi(av[5]);
	else
		(*s_data)->number_eat = -1;
	if (ft_initialize_philo(s_philo, s_data) == 0)
	{
		ft_free(*s_philo, *s_data, 'n', 'n');
		return (0);
	}
	return (1);
}
