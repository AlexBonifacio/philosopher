/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:22:11 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/21 18:53:08 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long ft_atol(const char *str)
{
	int	i;
	long nb;

	nb = 0;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			ft_exit("No negative values allowed");
		i++;
	}
	if (ft_strlen(str) > 10)
		ft_exit("You can't provide too large numbers");
	while (str[i])
	{
		nb = (nb * 10) + str[i] - '0';
		i++;
	}
	if (nb > 2147483647)
		ft_exit("Number is too large");
	return (nb);
}
