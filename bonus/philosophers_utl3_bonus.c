/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utl3_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 00:41:57 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/05/29 01:12:42 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

unsigned long long int	ft_get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

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

void	ft_free(t_philo *s_philo, t_data *s_data)
{
	if (s_data->array_id_process != NULL)
		free (s_data->array_id_process);
	if (s_data != NULL)
		free (s_data);
	if (s_philo != NULL)
		free (s_philo);
}
