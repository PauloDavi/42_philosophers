/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavi-al <pdavi-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:14:57 by pdavi-al          #+#    #+#             */
/*   Updated: 2023/11/23 23:07:54 by pdavi-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
		return (EXIT_FAILURE);
	if (!init_data(&data, argv))
	{
		if (data.philos != NULL)
			free(data.philos);
		return (EXIT_FAILURE);
	}
	philo_handler(&data);
	free_all(&data);
	return (EXIT_SUCCESS);
}
