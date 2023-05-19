/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 01:02:12 by alde-fre          #+#    #+#             */
/*   Updated: 2023/05/20 01:18:54 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
** Initialise the philosopher.
** Returns ERR if it fails else OK.
*/
t_ret	phil_init(
	t_phil *const phil,
	t_table *const table,
	t_tdata	const tdata,
	size_t const id)
{
	phil->id = id;
	phil->eating_counter = 0;
	phil->table = table;
	phil->tdata = tdata;
	if (pthread_mutex_init(&phil->fork, NULL))
		return (ERR);
	return (OK);
}

/*
** Destroys the philosopher.
*/
void	phil_destroy(t_phil *const phil)
{
	pthread_mutex_destroy(&phil->fork);
}

static inline void	__table_clear(t_table *const table, size_t const nb_philo)
{
	size_t	i;

	i = 0;
	while (i < nb_philo)
	{
		phil_destroy(table->tab + i);
		i++;
	}
	pthread_mutex_destroy(&table->m_running);
	free(table->tab);
}

/*
** Initialise the table of philosophers.
** Returns ERR if it fails, OK if success.
*/
t_ret	table_init(
	t_table *const table,
	size_t const nb_philo,
	t_tdata const tdata,
	size_t	const must_eat)
{
	size_t	i;

	table->tab = malloc(nb_philo * sizeof(t_phil));
	if (table->tab == NULL)
		return (ERR);
	table->size = nb_philo;
	table->total_satiated = 0;
	table->meal_goal = must_eat;
	if (pthread_mutex_init(&table->m_running, NULL))
		return (__table_clear(table, 0), ERR);
	i = 0;
	while (i < nb_philo)
	{
		if (phil_init(table->tab + i, table, tdata, i))
			return (__table_clear(table, i), ERR);
		i++;
	}
	table->running = -1;
	return (OK);
}

/*
** Destroys the table of philosophers.
*/
void	table_destroy(t_table *const table)
{
	__table_clear(table, table->size);
}
