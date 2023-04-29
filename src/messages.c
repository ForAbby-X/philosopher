/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 03:04:02 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/29 02:11:43 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static char const *const	g_msg[5] = {
"%09lu %lu has taken a fork\n",
"%09lu %lu is eating\n",
"%09lu %lu is sleeping\n",
"%09lu %lu is thinking\n",
"%09lu %lu died\n"
};

void	phil_msg(t_phil const *const phil, enum e_msg const msg)
{
	pthread_mutex_lock(&phil->table->m_running);
	if (phil->table->running == -1 || phil->table->running == phil->id)
		printf(g_msg[msg], get_timestamp(phil->tdata.time_start), phil->id + 1);
	pthread_mutex_unlock(&phil->table->m_running);
}
