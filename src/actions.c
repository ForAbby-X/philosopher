/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 01:01:54 by alde-fre          #+#    #+#             */
/*   Updated: 2023/05/23 05:26:13 by alde-fre         ###   ########.fr       */
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
	t_fork	*fork_1;
	t_fork	*fork_2;

	fork_1 = &phil->fork;
	fork_2 = &table_get(phil->table, phil->id + 1)->fork;
	if (phil->id & 1)
		__swap_add((void **)&fork_1, (void **)&fork_2);
	pthread_mutex_lock(fork_1);
	if (phil_stop_or_die(phil))
		return (pthread_mutex_unlock(fork_1), KO);
	phil_msg(phil, MSG_FORK);
	if (fork_1 == fork_2)
		return (msleep(phil, phil->tdata.time_to_die), phil_die(phil), KO);
	pthread_mutex_lock(fork_2);
	if (phil_stop_or_die(phil))
		return (pthread_mutex_unlock(fork_1), pthread_mutex_unlock(fork_2), KO);
	phil_msg(phil, MSG_FORK);
	phil_msg(phil, MSG_EATING);
	phil->tdata.last_eat = get_time_mili();
	msleep(phil, phil->tdata.time_to_eat);
	phil_add_meal(phil);
	pthread_mutex_unlock(fork_2);
	pthread_mutex_unlock(fork_1);
	return (phil_stop_or_die(phil));
}

t_ret	phil_sleep(t_phil *const phil)
{
	phil_msg(phil, MSG_SLEEPING);
	msleep(phil, phil->tdata.time_to_sleep);
	return (phil_stop_or_die(phil));
}

t_ret	phil_think(t_phil *const phil)
{
	phil_msg(phil, MSG_THINKING);
	if (phil->tdata.time_to_eat >= phil->tdata.time_to_sleep)
		msleep(phil, (phil->tdata.time_to_eat - phil->tdata.time_to_sleep + 1));
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
