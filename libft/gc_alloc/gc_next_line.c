/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_next_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 00:06:34 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/08 13:10:35 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_alloc.h"

static char	*ft_update_buffer(char *buffer)
{
	char	*eol;
	char	*start;
	char	*new;

	eol = ft_strchr(buffer, '\n');
	start = buffer;
	if (eol)
		start = eol + 1;
	if (!*start)
	{
		gc_free(buffer);
		return (NULL);
	}
	new = gc_alloc(ft_strlen(start) + 1);
	if (!new)
	{
		gc_free(buffer);
		return (NULL);
	}
	ft_strlcpy(new, start, ft_strlen(start) + 1);
	gc_free(buffer);
	return (new);
}

static char	*ft_get_line(char *buffer)
{
	char	*line;
	char	*eol;
	size_t	len;

	eol = ft_strchr(buffer, '\n');
	if (!eol)
		len = ft_strlen(buffer);
	if (eol)
		len = eol - buffer + 1;
	line = gc_alloc(len + 1);
	if (!line)
	{
		gc_free(buffer);
		return (NULL);
	}
	ft_strlcpy(line, buffer, len + 1);
	return (line);
}

static char	ft_read_helper(ssize_t bytes_read, char **aux, char **buffer)
{
	char	*old;

	if (bytes_read < 0)
	{
		gc_free(*aux);
		gc_free(*buffer);
		return (-1);
	}
	if (bytes_read == 0)
		return (1);
	aux[0][bytes_read] = '\0';
	old = *buffer;
	*buffer = gc_strjoin_gnl(*buffer, *aux);
	gc_free(old);
	if (!*buffer)
	{
		gc_free(*aux);
		return (-1);
	}
	if (ft_strchr(*buffer, '\n'))
		return (1);
	return (0);
}

static char	*ft_read(int fd, char *buffer)
{
	char	*aux;
	ssize_t	bytes_read;
	int		stopper;

	aux = gc_alloc(BUFFER_SIZE + 1);
	if (!aux)
	{
		gc_free(buffer);
		return (NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, aux, BUFFER_SIZE);
		stopper = ft_read_helper(bytes_read, &aux, &buffer);
		if (stopper < 0)
			return (NULL);
		if (stopper)
			break ;
	}
	gc_free(aux);
	return (buffer);
}

char	*gc_next_line(int fd, int free_static)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	if (BUFFER_SIZE < 1 || 0 > read(fd, 0, 0) || free_static)
	{
		gc_free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_get_line(buffer[fd]);
	if (!line)
		return (buffer[fd] = NULL, NULL);
	buffer[fd] = ft_update_buffer(buffer[fd]);
	if (!ft_strchr(line, '\n'))
	{
		gc_free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}
