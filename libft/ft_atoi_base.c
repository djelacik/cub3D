/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:42:51 by aapadill          #+#    #+#             */
/*   Updated: 2024/09/03 02:07:45 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @error
** -9223372036854775808 might be wrong
*/
static int	ft_overflow_check(long value, int digit, int base)
{
	if ((value == LONG_MAX / base && digit > LONG_MAX % base)
		|| value > LONG_MAX / base)
		return (1);
	return (0);
}

static int	ft_digit_value(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	else if (ft_isalpha(c))
		return (ft_tolower(c) - 'a' + 10);
	return (-1);
}

long	ft_atoi_base(const char *str, int base)
{
	long		pre;
	int			digit;
	int			overflow;

	while (((*str >= 9 && *str <= 13) || (*str == 32)) && str)
		str++;
	pre = 0;
	while (ft_digit_value(*str) != -1 && ft_digit_value(*str) < base)
	{
		digit = ft_digit_value(*str);
		overflow = ft_overflow_check(pre, digit, base);
		if (overflow == 1)
			return (LONG_MAX);
		pre = pre * base + digit;
		str++;
	}
	return (pre);
}
