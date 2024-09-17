/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:22:46 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/05/29 18:24:40 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_usleep(unsigned long long int time)
{
	unsigned long int	start;

	start = ft_get_time();
	while (1)
	{
		if (ft_get_time() - start > time)
			break ;
		usleep(100);
	}
}

int	ft_mutex_initializing(t_philo *s_philo)
{
	int	index;

	index = -1;
	while (++index < s_philo->ptr_data->number_thread)
	{
		if (pthread_mutex_init(&s_philo->ptr_data->fork[index], NULL) != 0)
		{
			ft_free(s_philo, s_philo->ptr_data, 'n', 'n');
			return (0);
		}
	}
	index = -1;
	while (++index < 2)
	{
		if (pthread_mutex_init(&s_philo->ptr_data->stop[index], NULL) != 0)
		{
			ft_free(s_philo, s_philo->ptr_data, 'y', 'n');
			return (0);
		}
	}
	return (1);
}

static void	*ft_action(void *data)
{
	t_philo	*s_philo;

	s_philo = data;
	s_philo->fork_left = &(s_philo->ptr_data->fork[s_philo->id - 1]);
	s_philo->fork_right = &(s_philo->ptr_data->fork[s_philo->id
			% s_philo->ptr_data->number_thread]);
	while (1)
	{
		ft_print_think(s_philo);
		pthread_mutex_lock(s_philo->fork_left);
		ft_print_tak_fork(s_philo);
		pthread_mutex_lock(s_philo->fork_right);
		ft_print_tak_fork(s_philo);
		pthread_mutex_lock(&(s_philo->ptr_data->stop[1]));
		s_philo->time_last_eat = ft_get_time();
		if (s_philo->ptr_data->number_eat != -1)
			s_philo->count_eat++;
		pthread_mutex_unlock(&(s_philo->ptr_data->stop[1]));
		ft_print_tak_eat(s_philo);
		pthread_mutex_unlock(s_philo->fork_right);
		pthread_mutex_unlock(s_philo->fork_left);
		ft_print_sleep(s_philo);
	}
	return (NULL);
}

static int	ft_creat_thread_even_id(t_philo *s_ph)
{
	int	i;

	i = 1;
	while (i < s_ph->ptr_data->number_thread)
	{
		if (pthread_create(&s_ph[i].thread, NULL, ft_action, &s_ph[i]) != 0)
		{
			ft_free(s_ph, s_ph->ptr_data, 'y', 'y');
			return (0);
		}
		i += 2;
		usleep(50);
	}
	return (1);
}

int	ft_creat_thread(t_philo *s_ph)
{
	int	i;

	i = 0;
	while (i < s_ph->ptr_data->number_thread)
	{
		if (pthread_create(&s_ph[i].thread, NULL, ft_action, &s_ph[i]) != 0)
		{
			ft_free(s_ph, s_ph->ptr_data, 'y', 'y');
			return (0);
		}
		usleep(50);
		i += 2;
	}
	if (ft_creat_thread_even_id(s_ph) == 0)
		return (0);
	if (ft_check_diiie(s_ph) == 0)
		return (-1);
	return (1);
}
