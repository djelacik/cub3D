/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_overflows.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:43:48 by aapadill          #+#    #+#             */
/*   Updated: 2024/08/08 12:32:55 by aapadill         ###   ########.fr       */
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

static int	ft_overflow_check_int(long value, int digit, int sign)
{
	if (value > INT_MAX / 10 || (value == INT_MAX / 10 && digit > 7))
		if (sign == 1)
			return (1);
	if (value > INT_MAX / 10 || (value == INT_MAX / 10 && digit > 8))
		if (sign == -1)
			return (1);
	return (0);
}

int	int_overflows(const char *str)
{
	const char	*start;
	int			sign;
	long		pre;
	int			digit;
	int			overflow;

	start = ft_jump_spaces(str);
	sign = ft_signer(*start);
	if (sign && !ft_isdigit(*start))
		start++;
	if (!ft_isdigit(*start))
		return (1);
	pre = 0;
	while (ft_isdigit(*start))
	{
		digit = *start - '0';
		overflow = ft_overflow_check_int(pre, digit, sign);
		if (overflow)
			return (1);
		pre = pre * 10 + digit;
		start++;
	}
	if (*start && !ft_isdigit(*start))
		return (1);
	return (0);
}
