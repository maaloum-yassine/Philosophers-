/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymaaloum <ymaaloum@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 06:40:57 by ymaaloum          #+#    #+#             */
/*   Updated: 2023/05/29 18:24:25 by ymaaloum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_put_err(char *str)
{
	write(1, "Error\n", 6);
	write(1, &str[0], ft_strlen(str));
	return (1);
}

int	ft_atoi(char *digit)
{
	int	res;
	int	index;

	index = 0;
	res = 0;
	if (digit[index] == '+')
		index++;
	while (digit[index])
		res = res * 10 + digit[index++] - '0';
	return (res);
}

static int	ft_check_isdigit_positif(char *av)
{
	int	index;

	index = 0;
	if (av[index] == '-')
		return (0);
	else if (av[index] == '+')
		index++;
	while (av[index])
	{
		if (av[index] < '0' || av[index] > '9')
			return (0);
		index++;
	}
	return (1);
}

static int	ft_check_arg(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_check_isdigit_positif(av[i]) == 1)
		{
			if ((i == 1 && ft_atoi(av[i]) == 0)
				|| (i == 5 && ft_atoi(av[i]) == 0))
				return (0);
			i++;
		}
		else
			return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_philo	*s_philo;
	t_data	*s_data;
	int		check;

	s_philo = NULL;
	s_data = NULL;
	if (ac == 5 || ac == 6)
	{
		if (ft_check_arg(av) == 0)
			return (ft_put_err("check your argument!\"|?-?|\"\n"));
		if (ft_initialize_data(ac, av, &s_philo, &s_data) == 0)
			return (ft_put_err("dynamic allocation malloc\"|?-?|\"\n"));
		if (ft_mutex_initializing(s_philo) == 0)
			return (ft_put_err("initializing mutex\"|?-?|\"\n"));
		check = ft_creat_thread(s_philo);
		if (check == 0)
			return (ft_put_err("creation thread\"|?-?|\"\n"));
		else if (check == -1)
			return (ft_put_err("thread detachment\"|?-?|\"\n"));
		ft_free(s_philo, s_data, 'y', 'y');
	}
	else
		return (ft_put_err("check your argument!\"|?-?|\"\n"));
	return (0);
}
