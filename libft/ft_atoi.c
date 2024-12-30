/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:11:21 by djelacik          #+#    #+#             */
/*   Updated: 2024/09/06 13:31:57 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_convert(const char *str, int sign)
{
	long long	ans;

	ans = 0;
	while (*str >= '0' && *str <= '9')
	{
		if (ans > INT_MAX || ans < INT_MIN)
		{
			if (sign == 1)
				return (2147483649);
			else
				return (2147483649);
		}
		ans = ans * 10 + *str - '0';
		str++;
	}
	return (ans * sign);
}

long	ft_atoi(const char *str)
{
	int			sign;

	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	return (ft_convert(str, sign));
}
