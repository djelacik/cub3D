/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:31:52 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/08 13:05:25 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_alloc.h"

void	*gc_calloc(size_t count, size_t size)
{
	void	*mem;

	if (size != 0 && ((SIZE_MAX / size) <= (count * size)))
		return (NULL);
	mem = gc_alloc(count * size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, count * size);
	return (mem);
}
