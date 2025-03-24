/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 08:07:06 by aapadill          #+#    #+#             */
/*   Updated: 2024/04/30 09:33:49 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*temp_dst;
	const char	*temp_src;

	if (!src && !dst)
		return (dst);
	temp_dst = (char *)dst;
	temp_src = (const char *)src;
	if ((const char *)src < (char *)dst)
		while (len--)
			*(temp_dst + len) = *(temp_src + len);
	else
		while (len--)
			*temp_dst++ = *temp_src++;
	return (dst);
}
