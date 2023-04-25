/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 20:24:09 by alde-fre          #+#    #+#             */
/*   Updated: 2023/04/25 23:50:06 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include "return.h"

typedef unsigned long					t_id;
typedef struct s_philosopher volatile	t_philosopher;
typedef struct s_table volatile			t_table;

t_ret	phil_init(t_philosopher *const phil, size_t const id);
void	phil_destroy(t_philosopher *const phil);

t_ret	table_init(t_table *const table, size_t	const nb_philo);
void	table_destroy(t_table *const table);

t_ret	table_run();

struct s_philosopher
{
	t_id			id;
	size_t			eating_counter;
	pthread_t		thread;
	pthread_mutex_t	fork;
};

struct s_table
{
	t_philosopher	*tab;
	size_t			size;
	t_id			running;
	pthread_mutex_t	m_running;
	pthread_mutex_t	m_printing;
};

#endif
