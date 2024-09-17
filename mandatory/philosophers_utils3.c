/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:43:29 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/05/29 18:57:20 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_pthread_detach(t_philo *s_philo)
{
	int	i;

	i = -1;
	while (++i < s_philo->ptr_data->number_thread)
	{
		if (pthread_detach(s_philo[i].thread) != 0)
			return (-1);
		i++;
	}
	return (1);
}

static int	ft_check_die(t_philo *s_ph)
{
	int	i;

	i = -1;
	while (++i < s_ph->ptr_data->number_thread)
	{
		pthread_mutex_lock(&(s_ph->ptr_data->stop[0]));
		pthread_mutex_lock(&(s_ph->ptr_data->stop[1]));
		if (ft_get_time() - s_ph[i].time_last_eat
			>= s_ph[i].ptr_data->time_to_die)
		{
			printf("%llu\t%d\tdied\n", ft_get_time()
				- s_ph->ptr_data->time_to_start, s_ph[i].id);
			return (ft_pthread_detach(s_ph));
		}
		else if (s_ph->ptr_data->number_eat != -1)
		{
			if (s_ph->count_eat > s_ph->ptr_data->number_eat)
				return (ft_pthread_detach(s_ph));
		}
		pthread_mutex_unlock(&(s_ph->ptr_data->stop[0]));
		pthread_mutex_unlock(&(s_ph->ptr_data->stop[1]));
	}
	return (0);
}

int	ft_check_diiie(t_philo *s_philo)
{
	while (1)
	{
		s_philo->ptr_data->check = ft_check_die(s_philo);
		if (s_philo->ptr_data->check == 1)
			break ;
		else if (s_philo->ptr_data->check == -1)
			return (0);
	}
	return (1);
}
