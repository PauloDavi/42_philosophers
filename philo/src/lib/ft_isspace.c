/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:16:45 by paulo             #+#    #+#             */
/*   Updated: 2023/11/20 09:16:54 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || (c == ' '))
		return (true);
	return (false);
}
