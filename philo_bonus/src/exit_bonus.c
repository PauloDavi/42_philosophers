/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 04:14:13 by paulo             #+#    #+#             */
/*   Updated: 2023/11/22 04:14:46 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
		kill(data->philo[i++].pid, SIGKILL);
	sem_close(data->sem_dead);
	sem_close(data->sem_print);
	sem_close(data->sem_stop);
	sem_close(data->sem_eat);
	sem_close(data->sem_forks);
	sem_unlink("dead");
	sem_unlink("message");
	sem_unlink("print");
	sem_unlink("eat");
	sem_unlink("forks");
	free(data->philo);
}
