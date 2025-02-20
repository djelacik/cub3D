/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:11:42 by aapadill          #+#    #+#             */
/*   Updated: 2025/02/20 17:24:27 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	vec_free(t_vec *src)
{
	if (!src || !src->alloc_size)
		return ;
	free(src->memory);
	src->memory = NULL;
	src->alloc_size = 0;
	src->elem_size = 0;
	src->len = 0;
}
