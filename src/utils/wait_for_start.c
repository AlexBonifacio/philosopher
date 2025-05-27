/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_start.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonifac <abonifac@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:58:55 by abonifac          #+#    #+#             */
/*   Updated: 2025/05/27 11:59:17 by abonifac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* Sleep for a short time to avoid busy CPU */
void wait_for_start(t_params *params)
{
	while (get_bool_mutex(&params->table_mutex, &params->rdy_to_start) == false)
	{
		usleep(100);
	}
}