/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:58:32 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/08 13:09:50 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_alloc.h"

char	*gc_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*joined;

	if (!s1 || !s2)
		return (NULL);
	str = gc_alloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	joined = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = 0;
	return (joined);
}

char	*gc_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	char	*joined;
	size_t	s1_len;
	size_t	s2_len;

	s1_len = 0;
	if (s1)
		s1_len = ft_strchr(s1, '\0') - s1;
	s2_len = ft_strchr(s2, '\0') - s2;
	str = gc_alloc(s1_len + s2_len + sizeof(char));
	if (!str)
		return (NULL);
	joined = str;
	while (s1 && *s1)
		*str++ = *s1++;
	while (s2 && *s2)
		*str++ = *s2++;
	*str = '\0';
	return (joined);
}
