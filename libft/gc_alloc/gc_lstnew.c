/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:26:04 by karpatel          #+#    #+#             */
/*   Updated: 2024/12/23 13:26:05 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "gc_alloc.h"

t_list	*gc_lstnew(void *content)
{
	t_list	*lstptr;

	lstptr = (gc_alloc(sizeof(t_list)));
	if (!lstptr)
		return (NULL);
	lstptr->content = content;
	lstptr->next = NULL;
	return (lstptr);
}
