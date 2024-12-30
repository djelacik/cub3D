/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:58:07 by djelacik          #+#    #+#             */
/*   Updated: 2024/05/03 11:06:06 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*add_node(t_list **new_list, void *content, void (*del)(void *))
{
	t_list	*node;

	node = ft_lstnew(content);
	if (!node)
	{
		free(content);
		ft_lstclear(new_list, del);
		return (NULL);
	}
	ft_lstadd_back(new_list, node);
	return (node);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*node;
	void	*result;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		result = f(lst->content);
		if (!result)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		node = add_node(&new_list, result, del);
		if (!node)
			return (NULL);
		lst = lst->next;
	}
	return (new_list);
}
