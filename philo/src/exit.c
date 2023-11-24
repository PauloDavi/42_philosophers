/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:43:36 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/11/23 23:11:24 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->philos[i].m_eat);
		pthread_mutex_destroy(&data->philos[i++].fork_l);
	}
	pthread_mutex_destroy(&data->m_print);
	pthread_mutex_destroy(&data->m_dead);
	free(data->philos);
}
