/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 01:02:31 by alde-fre          #+#    #+#             */
/*   Updated: 2023/05/20 01:02:32 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_time	get_time_mili(void)
{
	struct timeval		tv;
	unsigned long long	ret;

	gettimeofday(&tv, NULL);
	ret = tv.tv_sec * 1000;
	ret += tv.tv_usec / 1000;
	return (ret);
}

t_time	get_timestamp(t_time const last)
{
	return (get_time_mili() - last);
}
