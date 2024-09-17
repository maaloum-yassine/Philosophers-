/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:11:47 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/05/29 19:00:50 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	pthread_mutex_t		*fork;
	pthread_mutex_t		*stop;
	unsigned long int	time_to_die;
	unsigned long int	time_to_eat;
	unsigned long int	time_to_sleep;
	unsigned long int	time_to_start;
	int					number_thread;
	int					number_eat;
	int					check;
}t_data;

typedef struct s_philo
{
	t_data				*ptr_data;
	pthread_t			thread;
	pthread_mutex_t		*fork_left;
	pthread_mutex_t		*fork_right;
	unsigned long int	time_last_eat;
	int					count_eat;
	int					id;
}t_philo;

int						ft_strlen(char *str);
unsigned long long int	ft_get_time(void);
void					ft_usleep(unsigned long long int time);
int						ft_initialize_data(int ac, char **av, t_philo **s_philo,
							t_data **s_data);
int						ft_atoi(char *digit);
int						ft_mutex_initializing(t_philo *s_philo);
int						ft_creat_thread(t_philo *s_philo);
void					ft_print_think(t_philo *s_philo);
void					ft_print_tak_fork(t_philo *s_philo);
void					ft_print_tak_eat(t_philo *s_philo);
void					ft_print_sleep(t_philo *s_philo);
int						ft_check_diiie(t_philo *s_philo);
void					ft_free(t_philo *s_philo, t_data *s_data,
							char for_fork, char for_stop);
#endif
