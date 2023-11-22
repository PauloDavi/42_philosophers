/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 01:35:01 by paulo             #+#    #+#             */
/*   Updated: 2023/11/22 02:43:42 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdecorte42 <jdecorte42@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:15:25 by jdecorte42        #+#    #+#             */
/*   Updated: 2022/04/12 11:15:35 by jdecorte42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	is_dead(t_philo *philo, bool set_dead)
{
	pthread_mutex_lock(&philo->data->dead);
	if (set_dead)
		philo->data->stop = true;
	if (philo->data->stop)
	{
		pthread_mutex_unlock(&philo->data->dead);
		return (true);
	}
	pthread_mutex_unlock(&philo->data->dead);
	return (false);
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

	pthread_mutex_lock(&(philo->data->print));
	time = timestamp() - philo->data->t_start;
	if (!philo->data->stop && time >= 0 && !is_dead(philo, false))
		printf("%ld %ld %s", timestamp() - philo->data->t_start, philo->n, str);
	pthread_mutex_unlock(&(philo->data->print));
}

bool	philo_init(t_data *data, int i)
{
	data->philo[i].n = i + 1;
	data->philo[i].last_eat = 0;
	data->philo[i].fork_r = NULL;
	data->philo[i].data = data;
	data->philo[i].eat_count = 0;
	if (pthread_mutex_init(&(data->philo[i].fork_l), NULL) != 0)
		return (false);
	if (i == data->n_philo - 1)
		data->philo[i].fork_r = &data->philo[0].fork_l;
	else
		data->philo[i].fork_r = &data->philo[i + 1].fork_l;
	return (true);
}
