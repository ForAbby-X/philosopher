/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 23:43:28 by alde-fre          #+#    #+#             */
/*   Updated: 2023/04/28 04:14:57 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_ret	table_is_running(t_table *const table)
{
	t_ret	ret;

	pthread_mutex_lock(&table->m_running);
	ret = (table->running == -1);
	pthread_mutex_unlock(&table->m_running);
	return (ret);
}

t_ret	phil_stop_or_die(t_phil *const phil)
{
	if (!table_is_running(phil->table))
		return (KO);
	if (get_timestamp(phil->tdata.last_eat) >= phil->tdata.time_to_die)
		return (phil_die(phil), KO);
	return (OK);
}

void	phil_add_meal(t_phil *const phil)
{
	pthread_mutex_lock(&phil->table->m_running);
	if (phil->table->running == -1
		&& phil->tdata.nb_meal == phil->tdata.meal_goal)
	{
		phil->table->total_satiated++;
		if (phil->table->total_satiated >= phil->table->size)
			phil->table->running = phil->id;
	}
	pthread_mutex_unlock(&phil->table->m_running);
}

static inline void	*__phil_run(void *const data)
{
	t_phil *const	phil = data;

	while (!(phil_eat(phil) || phil_sleep(phil) || phil_think(phil)))
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
