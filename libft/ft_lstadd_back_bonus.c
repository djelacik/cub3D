/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:12:08 by aapadill          #+#    #+#             */
/*   Updated: 2024/06/12 17:48:32 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @description
** Adds the node ’new’ at the end of the list.
**
** @param
** lst: The address of a pointer to the first link of a list.
** new: The address of a pointer to the node to be added to the list.
**
** @return
*/

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	if (temp && new)
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}
