/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:22:11 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/28 22:56:50 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long ft_atol(const char *str)
{
	int i;
	long nb;

	nb = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			return ft_error("No negative values allowed");
		i++;
	}
	if (ft_strlen(str + i) > 10)
		return ft_error("You can't provide too large numbers");
	while (str[i])
	{
		nb = (nb * 10) + str[i] - '0';
		i++;
	}
	if (nb == 0)
		return ft_error("Something is wrong with arguments");
	if (nb > 2147483647)
		return ft_error("Number is too large");
	return (nb);
}
