/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:37:44 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/08 13:04:10 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_alloc.h"

/*
** @description
** Returns the global gc structure.
**
** @param
** None
**
** @return
** A pointer to the global gc structure.
*/
t_gc	*get_gc(void)
{
	static t_gc	gc = {NULL};

	return (&gc);
}

/*
** @description
** Allocates memory of the given size and tracks it using a linked list.
**
** @param
** size: The size of the memory block to allocate.
** @update
** bzero the allocated memory.
**
** @return
** A pointer to the allocated memory, or NULL if the allocation fails.
*/
void	*gc_alloc(size_t size)
{
	t_gc	*gc;
	void	*ptr;
	t_list	*node;

	gc = get_gc();
	if (!size)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = ft_lstnew(ptr);
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	ft_bzero(ptr, size);
	ft_lstadd_front(&(gc->head), node);
	return (ptr);
}

/*
** @description
** Frees a specific memory block and removes it from the tracking list.
**
** @param
** ptr: The pointer to the memory block to free.
**
** @return
** None
*/
void	gc_free(void *ptr)
{
	t_gc	*gc;
	t_list	*curr;
	t_list	*prev;

	if (!ptr)
		return ;
	gc = get_gc();
	curr = gc->head;
	prev = NULL;
	while (curr)
	{
		if (curr->content == ptr)
		{
			if (prev)
				prev->next = curr->next;
			else
				gc->head = curr->next;
			free(curr->content);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

void	gc_free_array(int n, void **ptr_array)
{
	while (n--)
		gc_free(ptr_array[n]);
	gc_free(ptr_array);
}

/*
** @description
** Frees all allocated memory blocks and clears the tracking list.
**
** @param
** None
**
** @return
** None
*/
void	gc_free_all(void)
{
	t_gc	*gc;
	t_list	*curr;
	t_list	*temp;

	gc = get_gc();
	curr = gc->head;
	while (curr)
	{
		temp = curr->next;
		if (curr -> content)
			free(curr->content);
		free(curr);
		curr = temp;
	}
	gc->head = NULL;
}
