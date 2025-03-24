/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:10:58 by aapadill          #+#    #+#             */
/*   Updated: 2024/06/12 07:57:22 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @brief
** Allocates and returns a new node. The member variable ’content’ is
** initialized with the value of the parameter ’content’. The variable
** ’next’ is initialized to NULL.
**
** @param
** content: The content to create the node with.
**
** @return
** The new node.
*/

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lstptr;

	lstptr = (malloc(sizeof(t_list)));
	if (!lstptr)
		return (NULL);
	lstptr->content = content;
	lstptr->next = NULL;
	return (lstptr);
}
