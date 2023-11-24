/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:42:05 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/11/23 23:09:24 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	check_args(char **argv);
static bool	init_mutex(t_data *data);
static bool	init_args(t_data *data, char **argv);

bool	init_data(t_data *data, char **argv)
{
	if (!check_args(argv))
	{
		printf("Invalid Arguments\n");
		return (false);
	}
	ft_memset(data, 0, sizeof(t_data));
	if (!init_mutex(data))
		return (false);
	data->n_philo = ft_atoi(argv[1]);
	if (data->n_philo <= 0)
		return (false);
	data->philos = malloc(sizeof(t_philo) * data->n_philo);
	if (data->philos == NULL)
		return (false);
	ft_memset(data->philos, 0, sizeof(t_philo) * data->n_philo);
	if (!init_args(data, argv))
	{
		printf("Invalid Arguments\n");
		return (false);
	}
	return (true);
}

static bool	check_args(char **argv)
{
	size_t	i;
	size_t	j;

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
	if (pthread_mutex_init(&data->m_print, NULL) != 0
		|| pthread_mutex_init(&data->m_dead, NULL) != 0)
		return (false);
	return (true);
}

static bool	init_args(t_data *data, char **argv)
{
	data->n_philo_eat = 0;
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
