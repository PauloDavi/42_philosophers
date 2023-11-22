/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:12:00 by paulo             #+#    #+#             */
/*   Updated: 2023/11/22 04:37:26 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*check_death(void *content);
static void	*philo_life(void *content);
static void	take_fork(t_philo *philo);
static void	philo_eat(t_philo *philo);

bool	philo_handler(t_data *data)
{
	int	i;

	data->t_start = timestamp();
	i = 0;
	while (i < data->n_philo)
		if (!philo_init(data, i++))
			return (false);
	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &philo_life,
				&(data->philo[i])) != 0)
			return (false);
		i++;
	}
	i = 0;
	while (i < data->n_philo)
		if (pthread_join(data->philo[i++].thread, NULL) != 0)
			return (false);
	return (true);
}

static void	*philo_life(void *content)
{
	t_philo		*philo;
	pthread_t	death;

	philo = content;
	if (philo->n % 2 == 0)
		msleep(philo->data->t_eat / 10);
	while (!is_dead(philo, false))
	{
		pthread_create(&death, NULL, check_death, content);
		take_fork(philo);
		philo_eat(philo);
		pthread_detach(death);
		if (philo->eat_count == philo->data->n_eat)
		{
			pthread_mutex_lock(&philo->data->m_stop);
			if (++philo->data->philo_eat == philo->data->n_philo)
			{
				pthread_mutex_unlock(&philo->data->m_stop);
				is_dead(philo, true);
			}
			pthread_mutex_unlock(&philo->data->m_stop);
			return (NULL);
		}
	}
	return (NULL);
}

static void	*check_death(void *content)
{
	t_philo	*philo;

	philo = content;
	msleep(philo->data->t_die + 1);
	pthread_mutex_lock(&philo->data->m_eat);
	pthread_mutex_lock(&philo->data->m_stop);
	if (!is_dead(philo, false) && timestamp()
		- philo->last_eat >= philo->data->t_die)
	{
		pthread_mutex_unlock(&philo->data->m_eat);
		pthread_mutex_unlock(&philo->data->m_stop);
		print(philo, "died\n");
		is_dead(philo, true);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->data->m_eat);
	pthread_mutex_unlock(&philo->data->m_stop);
	return (NULL);
}

static void	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_l));
	print(philo, "has taken a fork\n");
	if (philo->data->n_philo == 1)
	{
		msleep(philo->data->t_die * 2);
		return ;
	}
	pthread_mutex_lock((philo->fork_r));
	print(philo, "has taken a fork\n");
}

static void	philo_eat(t_philo *philo)
{
	print(philo, "is eating\n");
	pthread_mutex_lock(&(philo->data->m_eat));
	philo->last_eat = timestamp();
	philo->eat_count++;
	pthread_mutex_unlock(&(philo->data->m_eat));
	msleep(philo->data->t_eat);
	pthread_mutex_unlock((philo->fork_r));
	pthread_mutex_unlock(&(philo->fork_l));
	print(philo, "is sleeping\n");
	msleep(philo->data->t_sleep);
	print(philo, "is thinking\n");
}
