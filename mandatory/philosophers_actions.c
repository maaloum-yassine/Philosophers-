/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:27:53 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/05/19 17:46:20 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long long int	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	ft_print_think(t_philo *s_philo)
{
	pthread_mutex_lock(&(s_philo->ptr_data->stop[0]));
	printf("%llu\t%d\tis thinking\n", ft_get_time()
		- s_philo->ptr_data->time_to_start, s_philo->id);
	pthread_mutex_unlock(&(s_philo->ptr_data->stop[0]));
}

void	ft_print_tak_fork(t_philo *s_philo)
{
	pthread_mutex_lock(&(s_philo->ptr_data->stop[0]));
	printf("%llu\t%d\thas taken a fork\n", ft_get_time()
		- s_philo->ptr_data->time_to_start, s_philo->id);
	pthread_mutex_unlock(&(s_philo->ptr_data->stop[0]));
}

void	ft_print_tak_eat(t_philo *s_philo)
{
	pthread_mutex_lock(&(s_philo->ptr_data->stop[0]));
	printf("%llu\t%d\tis eating\n", ft_get_time()
		- s_philo->ptr_data->time_to_start, s_philo->id);
	pthread_mutex_unlock(&(s_philo->ptr_data->stop[0]));
	ft_usleep(s_philo->ptr_data->time_to_eat);
}

void	ft_print_sleep(t_philo *s_philo)
{
	pthread_mutex_lock(&(s_philo->ptr_data->stop[0]));
	printf("%llu\t%d\tis sleeping\n", ft_get_time()
		- s_philo->ptr_data->time_to_start, s_philo->id);
	pthread_mutex_unlock(&(s_philo->ptr_data->stop[0]));
	ft_usleep(s_philo->ptr_data->time_to_sleep);
}
