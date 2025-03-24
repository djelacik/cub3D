/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:29:26 by aapadill          #+#    #+#             */
/*   Updated: 2024/05/01 15:25:47 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @description
** Deletes and frees the given node and every 
** successor of that node, using the function ’del’
** and free(3).
** Finally, the pointer to the list must be set to NULL.
**
** @param
** lst: The address of a pointer to a node.
** del: The address of the function used to delete
** the content of the node.
**
** @return
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*node;
	t_list	*temp;

	if (lst)
	{
		node = *lst;
		while (node)
		{
			temp = node->next;
			ft_lstdelone(node, del);
			node = temp;
		}
		*lst = node;
	}
}
