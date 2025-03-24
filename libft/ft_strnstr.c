/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:16:25 by aapadill          #+#    #+#             */
/*   Updated: 2024/05/07 12:37:01 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @description
** Locates the first occurrence of the null-terminated string needle 
** in the string haystack, where not more than len characters are searched.
** Characters that appear after a ‘\0’ character are not searched. 
**
** @param
** *haystack: null-terminated string
** *needle: null terminated string
** len: max quantity of characters to search
**
** @return
** If needle is an empty string, haystack is returned;
** If needle occurs nowhere in haystack, NULL is returned;
** Otherwise a pointer to the first character of the first occurrence of 
** needle is returned.
*/

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*haystack_aux;
	const char	*needle_aux;
	size_t		n;

	if (!*needle)
		return ((char *)haystack);
	while (len && *haystack)
	{
		haystack_aux = haystack;
		needle_aux = needle;
		n = len;
		while (*haystack_aux == *needle_aux && *needle_aux && n)
		{
			haystack_aux++;
			needle_aux++;
			n--;
		}
		if (!*needle_aux)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
