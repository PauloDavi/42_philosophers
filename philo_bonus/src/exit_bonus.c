/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 04:14:13 by paulo             #+#    #+#             */
/*   Updated: 2023/11/23 23:51:55 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	free_all(t_data *data)
{
	int	i;

	i = 0;
	sem_close(data->sem_print);
	sem_close(data->sem_stop);
	sem_close(data->sem_eat);
	sem_close(data->sem_forks);
	sem_unlink("print");
	sem_unlink("stop");
	sem_unlink("eat");
	sem_unlink("forks");
	free(data->philos);
}
