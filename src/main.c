/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 05:02:42 by alde-fre          #+#    #+#             */
/*   Updated: 2023/04/27 17:28:20 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(void)
{
	t_table	table;

	if (table_init(&table, 5, 
		(t_tdata){0, 0, .time_to_die=800, .time_to_eat=200, .time_to_sleep=200}))
		return (1);
	if (table_run(&table))
		return (table_destroy(&table), 1);
	table_destroy(&table);
	return (0);
}
