/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-fre <alde-fre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 01:02:22 by alde-fre          #+#    #+#             */
/*   Updated: 2023/05/20 01:20:07 by alde-fre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static inline t_ret	__is_not_numbers(char const *const input)
{
	size_t	i;

	i = 0;
	if (input[i] == '-')
		i++;
	while (input[i])
	{
		if (input[i] < '0' || input[i] > '9')
			return (KO);
		i++;
	}
	return (OK);
}

static inline int	__atoi(char const *const input, t_ret *const err)
{
	size_t	i;
	int		sign;
	int		ret;

	i = 0;
	sign = 1;
	if (input[i] == '-')
	{
		sign = -1;
		i++;
	}
	ret = 0;
	while (input[i] >= '0' && input[i] <= '9')
	{
		if ((int)(ret * 10 + (input[i] - '0') - (sign == -1)) < 0)
			return (*err = KO, 0);
		ret = ret * 10 + (input[i] - '0');
		i++;
	}
	return (*err = OK, ret * sign);
}

static inline t_ret	__small_parse(t_time *const value, char const *const input)
{
	t_ret	error;

	if (__is_not_numbers(input))
		return (KO);
	*value = __atoi(input, &error);
	if (*value <= 0)
		return (KO);
	return (error);
}

t_ret	parse_input(
	t_table *const table,
	char *const *const input,
	int const count)
{
	t_tdata	tdata;
	t_time	nb_philo;
	t_time	must_eat;

	if (count < 5 || count > 6)
		return (KO);
	if (__small_parse(&nb_philo, input[1]))
		return (KO);
	if (__small_parse(&tdata.time_to_die, input[2]))
		return (KO);
	if (__small_parse(&tdata.time_to_eat, input[3]))
		return (KO);
	if (__small_parse(&tdata.time_to_sleep, input[4]))
		return (KO);
	must_eat = 0;
	if (count == 6)
		if (__small_parse(&must_eat, input[5]))
			return (KO);
	tdata.nb_meal = 0;
	tdata.meal_goal = must_eat;
	table_init(table, nb_philo, tdata, must_eat);
	return (OK);
}
