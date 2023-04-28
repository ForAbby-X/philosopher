/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 05:02:42 by alde-fre          #+#    #+#             */
/*   Updated: 2023/04/28 01:33:13 by mcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int const argc, char *const *const argv)
{
	t_table	table;

	if (parse_input(&table, argv, argc))
		return (1);
	if (table_run(&table))
		return (table_destroy(&table), 1);
	table_destroy(&table);
	return (0);
}
