/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 01:02:31 by alde-fre          #+#    #+#             */
/*   Updated: 2023/05/23 05:24:01 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

t_ret	msleep(t_phil *const phil, t_time const time)
{
	t_time const	target = get_time_mili() + time;

	while (get_time_mili() < target)
	{
		if (phil_stop_or_die(phil))
			return (KO);
		usleep(125);
	}
	return (OK);
}

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
