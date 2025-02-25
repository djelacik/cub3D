/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 15:12:44 by aapadill          #+#    #+#             */
/*   Updated: 2024/04/30 15:12:57 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** @brief
** Counts the number of nodes in a list
**
** @param
** lst: The beginning of the list.
** 
** @return
** The length of the list
*/

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
