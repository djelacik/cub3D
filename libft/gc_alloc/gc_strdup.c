/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:38:26 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/08 13:09:22 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_alloc.h"

char	*gc_strdup(const char *s1)
{
	size_t	len;
	char	*dest;
	char	*result;

	len = ft_strlen(s1);
	dest = gc_alloc((len + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	result = dest;
	while (*s1)
		*dest++ = *s1++;
	*dest = 0;
	return (result);
}
