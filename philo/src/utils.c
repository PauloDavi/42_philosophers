/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:35:01 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/11/24 00:02:40 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_dead(t_philo *philo, bool set_dead)
{
	bool	ret;

	pthread_mutex_lock(&philo->data->m_dead);
	if (set_dead)
		philo->data->stop = true;
	ret = philo->data->stop;
	pthread_mutex_unlock(&philo->data->m_dead);
	return (ret);
}

long int	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	msleep(int ms)
{
	long int	time;

	time = timestamp();
	while (timestamp() - time < ms)
		usleep(ms / 10);
}

void	print(t_philo *philo, char *str)
{
	long int	time;

	time = timestamp() - philo->data->t_start;
	if (!is_dead(philo, false))
	{
		pthread_mutex_lock(&(philo->data->m_print));
		printf("%ld %d %s", timestamp() - philo->data->t_start, philo->n, str);
		pthread_mutex_unlock(&(philo->data->m_print));
	}
}

bool	philo_init(t_data *data, int i)
{
	data->philos[i].n = i + 1;
	data->philos[i].data = data;
	data->philos[i].eat_count = 0;
	data->philos[i].t_last_eat = 0;
	data->philos[i].fork_r = NULL;
	if (pthread_mutex_init(&(data->philos[i].fork_l), NULL) != 0)
		return (false);
	if (pthread_mutex_init(&(data->philos[i].m_eat), NULL) != 0)
		return (false);
	if (i == data->n_philo - 1)
		data->philos[i].fork_r = &data->philos[0].fork_l;
	else
		data->philos[i].fork_r = &data->philos[i + 1].fork_l;
	return (true);
}
