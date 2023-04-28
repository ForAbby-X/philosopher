/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 04:20:13 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/28 03:43:17 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static inline void	__swap_add(void **const a, void **const b)
{
	void *const	c = *a;

	*a = *b;
	*b = c;
}

t_ret	phil_eat(t_phil *const phil)
{
	t_fork *fork_1 = &phil->fork;
	t_fork *fork_2 = &table_get(phil->table, phil->id + 1)->fork;

	if (phil->id & 1)
		__swap_add((void **)&fork_1, (void **)&fork_2);
	pthread_mutex_lock(fork_1);
	if (phil_stop_or_die(phil))
		return (pthread_mutex_unlock(fork_1), KO);
	phil_msg(phil, MSG_FORK);
	if (fork_1 == fork_2)
		return (usleep(phil->tdata.time_to_die * 1000), phil_die(phil), KO);
	pthread_mutex_lock(fork_2);
	if (phil_stop_or_die(phil))
		return (pthread_mutex_unlock(fork_1), pthread_mutex_unlock(fork_2), KO);
	phil_msg(phil, MSG_FORK);
	phil_msg(phil, MSG_EATING);
	phil->tdata.last_eat = get_time_mili();
	usleep(phil->tdata.time_to_eat * 1000);
	phil->tdata.nb_meal++;
	phil_add_meal(phil);
	pthread_mutex_unlock(fork_2);
	pthread_mutex_unlock(fork_1);
	return (phil_stop_or_die(phil));
}

t_ret	phil_sleep(t_phil *const phil)
{
	phil_msg(phil, MSG_SLEEPING);
	usleep(phil->tdata.time_to_sleep * 1000);
	return (phil_stop_or_die(phil));
}

t_ret	phil_think(t_phil *const phil)
{
	phil_msg(phil, MSG_THINKING);
	usleep((phil->tdata.time_to_die - (phil->tdata.time_to_eat + phil->tdata.time_to_sleep)) / 2 * 1000);
	return (phil_stop_or_die(phil));
}

void	phil_die(t_phil *const phil)
{
	t_table *const	table = phil->table;
	pthread_mutex_lock(&table->m_running);
	if (table->running == -1)
		table->running = phil->id;
	pthread_mutex_unlock(&table->m_running);
	phil_msg(phil, MSG_DIED);
}
