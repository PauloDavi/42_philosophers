/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 04:00:46 by paulo             #+#    #+#             */
/*   Updated: 2023/11/22 13:39:46 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	*check_death(void *content);
static void	philo_life(t_philo *philo);
static void	take_fork(t_philo *philo);
static void	philo_eat(t_philo *philo);

void	philo_handler(t_data *data)
{
	int	i;

	i = 0;
	data->t_start = timestamp();
	while (i < data->n_philo)
	{
		data->philo[i].pid = fork();
		if (data->philo[i].pid == 0)
		{
			philo_init(data, i);
			philo_life(&(data->philo[i]));
			exit(0);
		}
		i++;
	}
	i = 0;
	while (i < data->n_philo)
	{
		waitpid(data->philo[i++].pid, NULL, 0);
	}
}

static void	*check_death(void *content)
{
	t_philo	*philo;

	philo = content;
	msleep(philo->data->t_die + 1);
	sem_wait(philo->data->sem_eat);
	sem_wait(philo->data->sem_stop);
	if (!is_dead(philo, false) && timestamp()
		- philo->last_eat >= philo->data->t_die)
	{
		sem_post(philo->data->sem_eat);
		sem_post(philo->data->sem_stop);
		print(philo, "died\n");
		is_dead(philo, true);
		return (NULL);
	}
	sem_post(philo->data->sem_eat);
	sem_post(philo->data->sem_stop);
	return (NULL);
}

static void	philo_life(t_philo *philo)
{
	pthread_t	death;

	if (philo->n % 2 == 0)
		msleep(philo->data->t_eat / 10);
	while (!is_dead(philo, false))
	{
		pthread_create(&death, NULL, check_death, philo);
		take_fork(philo);
		philo_eat(philo);
		pthread_detach(death);
		if (philo->eat_count == philo->data->n_eat)
		{
			sem_wait(philo->data->sem_stop);
			if (++philo->data->philo_eat == philo->data->n_philo)
			{
				sem_post(philo->data->sem_stop);
				is_dead(philo, true);
			}
			sem_post(philo->data->sem_stop);
			return ;
		}
	}
}

static void	take_fork(t_philo *philo)
{
	sem_wait(philo->data->sem_forks);
	print(philo, "has taken a fork\n");
	if (philo->data->n_philo == 1)
	{
		msleep(philo->data->t_die * 2);
		return ;
	}
	sem_wait(philo->data->sem_forks);
	print(philo, "has taken a fork\n");
}

static void	philo_eat(t_philo *philo)
{
	print(philo, "is eating\n");
	sem_wait(philo->data->sem_eat);
	philo->last_eat = timestamp();
	philo->eat_count++;
	sem_post(philo->data->sem_eat);
	msleep(philo->data->t_eat);
	sem_post(philo->data->sem_forks);
	sem_post(philo->data->sem_forks);
	print(philo, "is sleeping\n");
	msleep(philo->data->t_sleep);
	print(philo, "is thinking\n");
}
