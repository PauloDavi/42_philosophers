/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:42:05 by paulo             #+#    #+#             */
/*   Updated: 2023/11/20 10:01:46 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	check_args(char **argv);
static bool	init_mutex(t_data *data);
static bool	init_args(t_data *data, char **argv);

bool	init_data(t_data *data, char **argv)
{
	ft_memset(data, 0, sizeof(t_data));
	if (!init_mutex(data))
		return (false);
	data->stop = false;
	if (!check_args(argv))
	{
		printf("Invalid Arguments\n");
		return (false);
	}
	data->n_philo = ft_atoi(argv[1]);
	if (data->n_philo <= 0)
		return (false);
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	if (data->philo == NULL)
		return (false);
	ft_memset(data->philo, 0, sizeof(t_philo) * data->n_philo);
	if (!init_args(data, argv))
	{
		printf("Invalid Arguments\n");
		return (false);
	}
	return (true);
}

static bool	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (ft_isspace(argv[i][j]))
			j++;
		if (argv[i][j] == '-' || argv[i][j] == '+')
			j++;
		if (argv[i][j] == '\0')
			return (false);
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static bool	init_mutex(t_data *data)
{
	if (pthread_mutex_init(&data->print, NULL) != 0
		|| pthread_mutex_init(&data->m_stop, NULL) != 0
		|| pthread_mutex_init(&data->m_eat, NULL) != 0
		|| pthread_mutex_init(&data->dead, NULL) != 0)
		return (false);
	return (true);
}

static bool	init_args(t_data *data, char **argv)
{
	data->philo_eat = 0;
	data->t_die = ft_atoi(argv[2]);
	data->t_eat = ft_atoi(argv[3]);
	data->t_sleep = ft_atoi(argv[4]);
	if (data->t_die <= 0 || data->t_eat <= 0 || data->t_sleep <= 0)
		return (false);
	if (argv[5] != NULL)
	{
		data->n_eat = ft_atoi(argv[5]);
		if (data->n_eat <= 0)
			return (false);
	}
	return (true);
}
