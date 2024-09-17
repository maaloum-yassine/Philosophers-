/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 18:40:44 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/05/29 15:53:17 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <signal.h>

typedef struct s_data
{
	sem_t				*fork;
	sem_t				*print;
	sem_t				*last_eat;
	unsigned long int	time_to_die;
	unsigned long int	time_to_eat;
	unsigned long int	time_to_sleep;
	unsigned long int	time_to_start;
	int					*array_id_process;
	int					number_process;
	int					number_eat;
}t_data;

typedef struct s_philo
{
	t_data				*ptr_data;
	pthread_t			thread;
	unsigned long int	time_last_eat;
	pid_t				pid;
	int					count_eat;
	int					id;
}t_philo;

int							ft_strlen(char *str);
int							ft_atoi(char *digit);
int							ft_put_err(char *str);
int							ft_initialize_data(int ac, char **av,
								t_philo **s_philo, t_data **s_data);
int							ft_creat_process(t_philo *s_philo);
unsigned long long int		ft_get_time(void);
void						ft_usleep(unsigned long long int time);
void						ft_print_think(t_philo *s_philo);
void						ft_print_tak_fork(t_philo *s_philo);
void						ft_print_tak_eat(t_philo *s_philo);
void						ft_print_sleep(t_philo *s_philo);
void						ft_free(t_philo *s_philo, t_data *s_data);
void						ft_kill_process(t_philo *s_philo);
#endif
