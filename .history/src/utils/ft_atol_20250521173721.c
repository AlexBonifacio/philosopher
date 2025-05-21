/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:22:11 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/21 17:37:21 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long ft_atol(const char *str)
{
	int	i;
	long nb;

	nb = 0;
	i = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == ' ')
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			ft_exit("No negative values allowed");
		i++;
	}
	while (str[i])
	{
		nb = (nb * 10) + str[i] + '0';
		i++;
	}
}