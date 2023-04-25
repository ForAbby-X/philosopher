/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 20:50:43 by alde-fre          #+#    #+#             */
/*   Updated: 2023/04/25 23:58:49 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
** Initialise the philosopher.
** Returns ERR if it fails.
*/
t_ret	phil_init(t_philosopher *const phil, size_t const id)
{
	phil->id = id;
	phil->eating_counter = 0;
	if (pthread_create(&phil->thread, NULL, phil->thread, NULL))
		return (ERR);
	if (pthread_mutex_init(&phil->fork, NULL))
		return (ERR);
}

/*
** Destroy the philosopher.
*/
void	phil_destroy(t_philosopher *const phil)
{
	pthread_mutex_destroy(&phil->fork);
}

static inline void	__table_clear(t_table *const table, size_t	const nb_philo)
{
	size_t	i;

	i = 0;
	while (i < nb_philo)
	{
		phil_destroy(table->tab + i);
		i++;
	}
	pthread_mutex_destroy(&table->m_running);
	pthread_mutex_destroy(&table->m_printing);
	free(table->tab);
}

/*
** Initialise the table of philosopher.
** Returns ERR if it fails, OK if success.
*/
t_ret	table_init(t_table *const table, size_t	const nb_philo)
{
	size_t	i;

	table->tab = malloc(nb_philo * sizeof(t_philosopher));
	if (table->tab == NULL)
		return (ERR);
	table->size = nb_philo;
	if (pthread_mutex_init(&table->m_running, NULL))
		return (__table_clear(table, 0), ERR);
	if (pthread_mutex_init(&table->m_printing, NULL))
		return (__table_clear(table, 0), ERR);
	i = 0;
	while (i < nb_philo)
	{
		if (phil_init(table->tab + i, i) == ERR)
			return (__table_clear(table, i), ERR);
		i++;
	}
	table->running = 0;
	return (OK);
}

/*
** Destroy the table of philosopher.
*/
void	table_destroy(t_table *const table)
{
	__table_clear(table, table->size);
}
