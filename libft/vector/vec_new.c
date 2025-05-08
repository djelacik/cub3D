/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:09:30 by aapadill          #+#    #+#             */
/*   Updated: 2025/02/20 17:07:22 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_new(t_vec *dst, size_t init_len, size_t elem_size)
{
	if (!dst || !elem_size)
		return (-1);
	dst->alloc_size = init_len * elem_size;
	dst->len = 0;
	dst->elem_size = elem_size;
	if (!init_len)
		dst->memory = NULL;
	else
	{
		dst->memory = gc_alloc(dst->alloc_size);
		if (!dst->memory)
			return (-1);
	}
	return (1);
}
