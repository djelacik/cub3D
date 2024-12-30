/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:45:52 by djelacik          #+#    #+#             */
/*   Updated: 2024/05/03 10:39:05 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*buffer;

	if (!s || !*s)
		return (ft_strdup(""));
	if (!len || start > ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	buffer = ft_calloc(len + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	ft_strlcpy(buffer, &s[start], len + 1);
	return (buffer);
}
