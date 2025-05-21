/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:31:58 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/21 18:05:16 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_exit(char *str)
{
	printf(RED BOLD"Error: " RESET"%s\n", str);
	exit(EXIT_FAILURE);
}