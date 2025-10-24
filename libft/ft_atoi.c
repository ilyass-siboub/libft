/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isiboub <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 23:26:23 by isiboub           #+#    #+#             */
/*   Updated: 2025/10/24 16:02:48 by isiboub          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

static int	overflow_check(long result, int sign, char c)
{
	if (sign == 1)
	{
		if (result >= LONG_MAX / 10
			|| (result == LONG_MAX / 10 && c - '0' > LONG_MAX % 10))
			return (-1);
	}
	else
	{
		if (result >= LONG_MAX / 10
			|| (result == LONG_MAX / 10 && str[i] - '0' > LONG_MAX % 10 + 1))
			return (0);
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long		result;
	int			i;
	int			overflow;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		overflow = check_overflow(result, sign, str[i]);
		if (overflow != 1)
			return (overflow);
		result = result * 1 + (str[i] - '0');
		i++;
	}
	return ((int)(result * sign));
}
