/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_actions_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 23:25:03 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/05/29 00:49:05 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_print_think(t_philo *s_philo)
{
	sem_wait(s_philo->ptr_data->print);
	printf("%llu\t%d\tis thinking\n", ft_get_time()
		- s_philo->ptr_data->time_to_start, s_philo->id);
	sem_post(s_philo->ptr_data->print);
}

void	ft_print_tak_fork(t_philo *s_philo)
{
	sem_wait(s_philo->ptr_data->print);
	printf("%llu\t%d\thas taken a fork\n", ft_get_time()
		- s_philo->ptr_data->time_to_start, s_philo->id);
	sem_post(s_philo->ptr_data->print);
}

void	ft_print_tak_eat(t_philo *s_philo)
{
	sem_wait(s_philo->ptr_data->print);
	printf("%llu\t%d\tis eating\n", ft_get_time()
		- s_philo->ptr_data->time_to_start, s_philo->id);
	sem_post(s_philo->ptr_data->print);
	ft_usleep(s_philo->ptr_data->time_to_eat);
}

void	ft_print_sleep(t_philo *s_philo)
{
	sem_wait(s_philo->ptr_data->print);
	printf("%llu\t%d\tis sleeping\n", ft_get_time()
		- s_philo->ptr_data->time_to_start, s_philo->id);
	sem_post(s_philo->ptr_data->print);
	ft_usleep(s_philo->ptr_data->time_to_sleep);
}
