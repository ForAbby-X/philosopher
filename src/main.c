/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 01:02:04 by alde-fre          #+#    #+#             */
/*   Updated: 2023/05/20 01:02:06 by alde-fre         ###   ########.fr       */
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
