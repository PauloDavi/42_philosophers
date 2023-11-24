/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 04:00:46 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/11/23 23:59:55 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

static void	*check_death(void *content);
static void	philo_life(t_philo *philo);
static void	take_fork(t_philo *philo);
static void	philo_eat(t_philo *philo);

void	philo_handler(t_data *data)
{
	int			i;
	pthread_t	stop;

	i = 0;
	while (i < data->n_philo)
		philo_init(data, i++);
	i = 0;
	sem_wait(data->sem_stop);
	data->t_start = timestamp();
	while (i < data->n_philo)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == 0)
			philo_life(&(data->philos[i]));
		i++;
	}
	pthread_create(&stop, NULL, stop_handler, data);
	pthread_detach(stop);
	i = 0;
	while (i < data->n_philo)
		waitpid(data->philos[i++].pid, NULL, 0);
	sem_post(data->sem_stop);
}

static void	*check_death(void *content)
{
	t_philo	*philo;

	philo = content;
	msleep(philo->data->t_die + 1);
	sem_wait(philo->data->sem_eat);
	if ((timestamp() - philo->t_last_eat) >= philo->data->t_die)
	{
		if (philo->data->n_eat != 0 && philo->eat_count == philo->data->n_eat)
			return (NULL);
		sem_post(philo->data->sem_eat);
		print(philo, "died\n");
		sem_post(philo->data->sem_stop);
		return (NULL);
	}
	sem_post(philo->data->sem_eat);
	return (NULL);
}

static void	philo_life(t_philo *philo)
{
	pthread_t	death;

	while (true)
	{
		pthread_create(&death, NULL, check_death, philo);
		take_fork(philo);
		philo_eat(philo);
		pthread_detach(death);
		if (philo->data->n_eat != 0 && philo->eat_count == philo->data->n_eat)
			exit(EXIT_SUCCESS);
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
	philo->t_last_eat = timestamp();
	philo->eat_count++;
	sem_post(philo->data->sem_eat);
	msleep(philo->data->t_eat);
	sem_post(philo->data->sem_forks);
	sem_post(philo->data->sem_forks);
	print(philo, "is sleeping\n");
	msleep(philo->data->t_sleep);
	print(philo, "is thinking\n");
}
