/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:07:24 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/12 16:46:20 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*buffer;
	char	*p;

	buffer = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!buffer)
		return (NULL);
	p = buffer;
	while (*s1)
		*buffer++ = *s1++;
	while (*s2)
		*buffer++ = *s2++;
	*buffer++ = 0;
	return (p);
}
