/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 08:23:37 by aapadill          #+#    #+#             */
/*   Updated: 2024/04/29 17:22:03 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_exp(int base, int exp)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	while (i < exp)
	{
		result *= base;
		i++;
	}
	return (result);
}

static int	ft_digit_counter(int j)
{
	int	i;

	i = 1;
	while (j >= 10)
	{
		j /= 10;
		i++;
	}
	return (i);
}

static int	signer(int n)
{
	int	sign;

	sign = 0;
	if (n < 0)
		sign = 1;
	return (sign);
}

char	*ft_itoa(int n)
{
	int		digits;
	int		sign;
	char	*str;
	int		j;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = signer(n);
	if (sign)
		n = -n;
	digits = ft_digit_counter(n);
	str = malloc((digits + sign + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (sign)
		str[0] = '-';
	j = 0;
	while (j < digits)
	{
		str[j + sign] = (n / ft_exp(10, digits - j - 1)) % 10 + '0';
		n %= ft_exp(10, digits - j - 1);
		j++;
	}
	str[digits + sign] = 0;
	return (str);
}
