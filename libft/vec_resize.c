/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:10:50 by aapadill          #+#    #+#             */
/*   Updated: 2025/02/21 10:03:16 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_resize(t_vec *src, size_t target_len)
{
	t_vec	dst;

	if (!src)
		return (-1);
	else if (!src->memory)
		return (vec_new(src, target_len, src->elem_size));
	else if (vec_new(&dst, target_len, src->elem_size) < 0)
		return (-1);
	ft_memcpy(dst.memory, src->memory, src->len * src->elem_size);
	dst.len = src->len;
	vec_free(src);
	*src = dst;
	return (1);
}
