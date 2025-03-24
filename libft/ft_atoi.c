/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:55:08 by aapadill          #+#    #+#             */
/*   Updated: 2024/08/06 17:53:47 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*ft_jump_spaces(const char *str)
{
	while (((*str >= 9 && *str <= 13) || (*str == 32)) && str)
		str++;
	return (str);
}

static int	ft_signer(const char c)
{
	if (c == '-')
		return (-1);
	if (ft_isdigit(c) || c == '+')
		return (1);
	return (0);
}

/*
** @error
** -9223372036854775808 might be wrong
*/

static int	ft_overflow_check(long value, int digit, int sign)
{
	if (value > LONG_MAX / 10 || (value == LONG_MAX / 10 && digit > 7))
	{
		if (sign == 1)
			return (1);
		else
			return (-1);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	const char	*start;
	int			sign;
	long long	pre;
	int			digit;
	int			overflow;

	start = ft_jump_spaces(str);
	sign = ft_signer(*start);
	if (sign && !ft_isdigit(*start))
		start++;
	pre = 0;
	while (ft_isdigit(*start))
	{
		digit = *start - '0';
		overflow = ft_overflow_check(pre, digit, sign);
		if (overflow == 1)
			return ((int)LLONG_MAX);
		if (overflow == -1)
			return ((int)LLONG_MIN);
		pre = pre * 10 + digit;
		start++;
	}
	pre = pre * sign;
	return ((int)pre);
}
