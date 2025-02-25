/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:47:53 by aapadill          #+#    #+#             */
/*   Updated: 2024/06/12 08:21:56 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @description
** Iterates the list ’lst’ and applies the function ’f’ on the content of each
** node. 
** Creates a new list resulting of the successive applications of the function 
** ’f’. 
** The ’del’ function is used to delete the content of a node if needed.
**
** @param
** lst: The address of a pointer to a node. 
** f: The address of the function used to iterate on the list.
** del: The address of the function used to delete the content of a node if 
** needed.
**
** @return
** The new list.
** NULL if the allocation fails.
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*mapped;
	t_list	*node;
	void	*new_content;

	mapped = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		if (!new_content)
		{
			ft_lstclear(&mapped, del);
			break ;
		}
		node = ft_lstnew(new_content);
		if (!node)
		{
			del(new_content);
			ft_lstclear(&mapped, del);
			break ;
		}
		ft_lstadd_back(&mapped, node);
		lst = lst->next;
	}
	return (mapped);
}
