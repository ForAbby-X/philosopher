/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 23:43:28 by alde-fre          #+#    #+#             */
/*   Updated: 2023/04/27 17:13:30 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static inline t_ret	__table_is_running(t_table *const table)
{
	t_ret	ret;

	pthread_mutex_lock(&table->m_running);
	ret = (table->running == -1);
	pthread_mutex_unlock(&table->m_running);
	return (ret);
}

t_ret	phil_stop_or_die(t_phil *const phil)
{
	if (!__table_is_running(phil->table))
		return (KO);
	if (get_timestamp(phil->tdata.last_eat) >= phil->tdata.time_to_die)
		return (phil_die(phil), KO);
	return (OK);
}

t_ret	phil_loop(t_phil *const phil)
{
	if (phil_eat(phil) || phil_sleep(phil) || phil_think(phil))
		return (KO);
	return (OK);
}

static inline void	*__phil_run(void *const data)
{
	t_phil *const	self = data;

	while (!phil_loop(self))
		;
	return (NULL);
}

t_ret	table_run(t_table *const table)
{
	size_t			i;
	t_phil			*phil;
	t_time const	time_start = get_time_mili();

	i = 0;
	while (i < table->size)
	{
		phil = table_get(table, i);
		phil->tdata.last_eat = time_start;
		phil->tdata.time_start = time_start;
		if (pthread_create(&phil->thread, NULL, &__phil_run, phil))
			return (ERR);
		i++;
	}
	i = 0;
	while (i < table->size)
	{
		if (pthread_join(table_get(table, i)->thread, NULL))
			return (ERR);
		i++;
	}
	return (OK);
}
