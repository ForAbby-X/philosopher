/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 01:01:59 by alde-fre          #+#    #+#             */
/*   Updated: 2023/05/20 01:02:01 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

/*
** Returns the philosopher at the index
** (if the index is out of bound it get looped)
*/
t_phil	*table_get(t_table *const table, t_id const id)
{
	if (id < 0L || id >= (long)table->size)
		return (table->tab + (id % table->size));
	return (table->tab + id);
}
