/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:42:10 by karpatel          #+#    #+#             */
/*   Updated: 2024/12/25 11:42:12 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_alloc.h"

char	*gc_strndup(char *s, int n)
{
	char	*dest;
	int		i;

	dest = gc_alloc((n + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
