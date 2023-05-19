/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 20:24:09 by alde-fre          #+#    #+#             */
/*   Updated: 2023/05/20 01:24:01 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include "return.h"

// ## type definitions ## //
typedef long					t_id;
typedef pthread_mutex_t			t_fork;
typedef int						t_time;
typedef struct s_philosopher	t_phil;
typedef struct s_table			t_table;

// ## structures ## //
typedef struct s_time_data
{
	t_time			last_eat;
	t_time			time_start;
	t_time			time_to_die;
	t_time			time_to_eat;
	t_time			time_to_sleep;
	size_t			nb_meal;
	size_t			meal_goal;
}	t_tdata;

struct s_philosopher
{
	t_id			id;
	size_t			eating_counter;
	t_table			*table;
	pthread_t		thread;
	t_fork			fork;
	t_tdata			tdata;
};

struct s_table
{
	t_phil			*tab;
	size_t			size;
	size_t			total_satiated;
	size_t			meal_goal;
	t_id			running;
	pthread_mutex_t	m_running;
};

// ## enumerations ## //
enum e_msg{
	MSG_FORK,
	MSG_EATING,
	MSG_SLEEPING,
	MSG_THINKING,
	MSG_DIED
};

// ## parsing ## //
t_ret	parse_input(
			t_table *const table,
			char *const *const input,
			int const count);

// ## philosopher ## //
t_ret	phil_init(
			t_phil *const phil,
			t_table *const table,
			t_tdata	const tdata,
			size_t const id);
void	phil_destroy(t_phil *const phil);

// ## table ## //
t_ret	table_init(
			t_table *const table,
			size_t	const nb_philo,
			t_tdata const tdata,
			size_t	const must_eat);
void	table_destroy(t_table *const table);

// ## geter ## //
t_phil	*table_get(t_table *const table, t_id const id)
		__attribute__((always_inline));

// ## time ## //
t_time	get_time_mili(void)
		__attribute__((always_inline));
t_time	get_timestamp(t_time const last)
		__attribute__((always_inline));

// ## messages ## //
void	phil_msg(t_phil const *const phil, enum e_msg const msg)
		__attribute__((always_inline));

// ## actions ## //
t_ret	phil_eat(t_phil *const phil);
t_ret	phil_sleep(t_phil *const phil);
t_ret	phil_think(t_phil *const phil);
void	phil_die(t_phil *const phil);

// ## simulation ## //
t_ret	table_is_running(t_table *const table)
		__attribute__((always_inline));
t_ret	phil_stop_or_die(t_phil *const phil)
		__attribute__((always_inline));
void	phil_add_meal(t_phil *const phil)
		__attribute__((always_inline));
t_ret	table_run(t_table *const table)
		__attribute__((always_inline));

#endif
