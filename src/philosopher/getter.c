/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcourtoi <mcourtoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 22:19:00 by mcourtoi          #+#    #+#             */
/*   Updated: 2023/04/27 03:56:19 by mcourtoi         ###   ########.fr       */
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
