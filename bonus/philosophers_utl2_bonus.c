/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utl2_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 00:03:35 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/05/29 18:39:19 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_free_semaphore(t_philo *s_philo)
{
	sem_close(s_philo->ptr_data->fork);
	sem_close(s_philo->ptr_data->print);
	sem_close(s_philo->ptr_data->last_eat);
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/last_eat");
}

void	ft_kill_process(t_philo *s_philo)
{
	int	i;

	i = -1;
	ft_free_semaphore(s_philo);
	while (++i < s_philo->ptr_data->number_process)
	{
		if (s_philo->ptr_data->array_id_process[i] != 0)
			kill(s_philo->ptr_data->array_id_process[i], SIGTERM);
	}
	ft_free(s_philo, s_philo->ptr_data);
}

static void	*ft_check_die(void *data)
{
	t_philo	*s_ph;

	s_ph = data;
	while (1)
	{
		sem_wait(s_ph->ptr_data->last_eat);
		if (ft_get_time() - s_ph->time_last_eat
			>= s_ph->ptr_data->time_to_die)
		{
			sem_wait(s_ph->ptr_data->print);
			printf("%llu\t%d\tdied\n", ft_get_time()
				- s_ph->ptr_data->time_to_start, s_ph->id);
			exit(0);
			sem_post(s_ph->ptr_data->print);
		}
		else if (s_ph->ptr_data->number_eat != -1)
		{
			if (s_ph->count_eat > s_ph->ptr_data->number_eat + 2)
			{
				sem_wait(s_ph->ptr_data->print);
				exit(0);
			}
		}
		sem_post(s_ph->ptr_data->last_eat);
	}
}

static void	ft_action(t_philo *s_philo)
{
	pthread_create(&s_philo->thread, NULL, ft_check_die, &(s_philo[0]));
	while (1)
	{
		ft_print_think(s_philo);
		sem_wait(s_philo->ptr_data->fork);
		ft_print_tak_fork(s_philo);
		sem_wait(s_philo->ptr_data->fork);
		ft_print_tak_fork(s_philo);
		sem_wait(s_philo->ptr_data->last_eat);
		s_philo->time_last_eat = ft_get_time();
		if (s_philo->ptr_data->number_eat != -1)
			s_philo->count_eat++;
		sem_post(s_philo->ptr_data->last_eat);
		ft_print_tak_eat(s_philo);
		sem_post(s_philo->ptr_data->fork);
		sem_post(s_philo->ptr_data->fork);
		ft_print_sleep(s_philo);
	}
	pthread_join(s_philo->thread, NULL);
}

int	ft_creat_process(t_philo *s_philo)
{
	int	i;

	i = -1;
	while (++i < s_philo->ptr_data->number_process)
	{
		s_philo[i].pid = fork();
		if (s_philo[i].pid == -1)
		{
			ft_kill_process(s_philo);
			return (-1);
		}
		else if (s_philo[i].pid == 0)
			ft_action(&s_philo[i]);
		else
			s_philo->ptr_data->array_id_process[i] = s_philo[i].pid;
	}
	return (1);
}
