/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:28:31 by djelacik          #+#    #+#             */
/*   Updated: 2024/05/03 10:38:42 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*buffer;
	unsigned int	i;

	if (!s || !f)
		return (0);
	buffer = ft_strdup(s);
	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i])
	{
		buffer[i] = f(i, s[i]);
		i++;
	}
	return (buffer);
}
