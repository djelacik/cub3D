/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_alloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:23:36 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/08 13:16:51 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_ALLOC_H
# define GC_ALLOC_H

# include "libft.h"

typedef struct s_garbage_collector
{
	t_list	*head;
}	t_gc;

void	*gc_alloc(size_t size);
void	gc_free(void *ptr);
void	gc_free_array(int n, void **ptr_array);
void	gc_free_all(void);

char	*gc_itoa(int n);
char	*gc_next_line(int fd, int free_static);
char	**gc_split(char const *s, char c, int *n);
char	*gc_strdup(const char *s1);
char	*gc_strjoin(char const *s1, char const *s2);
char	*gc_strjoin_gnl(char *s1, char *s2);
char	*gc_substr(char const *s, unsigned int start, size_t len);
void	*gc_calloc(size_t count, size_t size);
char	*gc_strndup(char *s, int n);
t_list	*gc_lstnew(void *content);

#endif
