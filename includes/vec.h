/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:14:01 by aapadill          #+#    #+#             */
/*   Updated: 2025/02/21 13:20:04 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include <unistd.h>
# include <stdbool.h>
# include "libft.h"
# include "gc_alloc.h"

typedef struct s_vec
{
	unsigned char	*memory;
	size_t			elem_size;
	size_t			alloc_size;
	size_t			len;
}	t_vec;

int		vec_new(t_vec *src, size_t init_len, size_t elem_size);
void	vec_free(t_vec *src);
//int		vec_from(t_vec *dst, void *src, size_t len, size_t elem_size);
int		vec_resize(t_vec *src, size_t target_len);
//int		vec_clear(t_vec *src);
int		vec_push(t_vec *src, void *elem);
//int		vec_pop(void *dst, t_vec *src);
//int		vec_copy(t_vec *dst, t_vec *src);
void	*vec_get(t_vec *src, size_t index);
//int		vec_insert(t_vec *dst, void *elem, size_t index);
//int		vec_remove(t_vec *src, size_t index);
//int		vec_append(t_vec *dst, t_vec *src);
//int		vec_prepend(t_vec *dst, t_vec *src);

#endif
