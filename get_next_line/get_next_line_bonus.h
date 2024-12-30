/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:33:29 by djelacik          #+#    #+#             */
/*   Updated: 2024/07/04 13:50:59 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

// <limits.h> included for OPEN_MAX: number of
// fd a process can have open at the same time.

# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 4096
# endif

//Function prototypes

char	*get_next_line(int fd);

size_t	ft_strlen2(const char *s);
char	*clean_up(char **buffer);
char	*small_clean(char **buffer);
char	*ft_strchr2(const char *s, int c);
void	*ft_calloc2(size_t count, size_t size);
char	*ft_strjoin_free(char *line, char const *buffer);
void	*ft_memcpy2(void *dst, const void *src, size_t n, int flag);
#endif