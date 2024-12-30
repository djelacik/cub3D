/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum_or_underscore.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 09:37:42 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/20 10:18:13 by mjaakkol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum_or_underscore(char *str)
{
	int		i;

	i = 1;
	while (str[i])
	{
		if ((str[i] < 'A' || str[i] > 'Z') && (str[i] < 'a' || str[i] > 'z')
			&& (str[i] < '0' || str[i] > '9') && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
