/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:39:45 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/13 17:45:45 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(char *str)
{
	while (*str)
	{
		if (*str == '-' || *str == '+')
			str++;
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}