/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:55:37 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/08 13:10:13 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @description
** Allocates with malloc(3) and returns a subtring from the string 's'.
** The substring begins at index 'start' and is of maximum size of 'len'.
**
** @param
** s: The string from which to create the substring.
** start: The start index of the substring in the string 's'.
** len: The maximum length of the substring.
**
** @return
** The substring (pointer to the new allocated string in the heap).
** NULL if malloc fails.
*/

#include "gc_alloc.h"

char	*gc_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	s_len;
	size_t	writable;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (gc_strdup(""));
	writable = len;
	if (s_len - start < len)
		writable = s_len - start;
	sub = gc_alloc(writable + 1);
	if (!sub)
		return (NULL);
	ft_strlcpy(sub, s + start, writable + 1);
	return (sub);
}
