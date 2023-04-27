/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 03:04:02 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/27 17:02:00 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static const char	*g_msg[5] = {
"%09lu %lu has taken a fork\n",
"%09lu %lu is eating\n",
"%09lu %lu is sleeping\n",
"%09lu %lu is thinking\n",
"%09lu %lu died\n"
};

void	phil_msg(t_phil const *const phil, enum e_msg msg)
{
	pthread_mutex_lock(&phil->table->m_printing);
	printf(g_msg[msg], get_timestamp(phil->tdata.time_start), phil->id + 1);
	pthread_mutex_unlock(&phil->table->m_printing);
}
