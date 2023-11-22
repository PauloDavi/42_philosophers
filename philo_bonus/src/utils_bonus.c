/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 04:00:05 by paulo             #+#    #+#             */
/*   Updated: 2023/11/22 13:35:39 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	philo_init(t_data *data, int i)
{
	data->philo[i].n = i + 1;
	data->philo[i].last_eat = 0;
	data->philo[i].data = data;
	data->philo[i].eat_count = 0;
}

bool	is_dead(t_philo *philo, bool set_dead)
{
	sem_wait(philo->data->sem_dead);
	if (set_dead)
		philo->data->stop = true;
	if (philo->data->stop)
	{
		sem_post(philo->data->sem_dead);
		return (true);
	}
	sem_post(philo->data->sem_dead);
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

	sem_wait(philo->data->sem_print);
	time = timestamp() - philo->data->t_start;
	if (!philo->data->stop && time >= 0 && !is_dead(philo, false))
		printf("%ld %ld %s", timestamp() - philo->data->t_start, philo->n, str);
	sem_post(philo->data->sem_print);
}
