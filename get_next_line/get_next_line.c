/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 11:58:36 by djelacik          #+#    #+#             */
/*   Updated: 2024/07/04 13:49:35 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*clean_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (buffer[i] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	new = ft_calloc2(ft_strlen2(buffer + i) + 1, 1);
	if (!new)
	{
		free(buffer);
		return (NULL);
	}
	j = 0;
	while (buffer[i] != '\0')
		new[j++] = buffer[i++];
	free(buffer);
	return (new);
}

static char	*read_to_buffer(int fd, char *buffer)
{
	char	*temp_buffer;
	int		bytes_read;

	temp_buffer = ft_calloc2(BUFFER_SIZE + 1, 1);
	if (!temp_buffer)
		return (small_clean(&buffer));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (small_clean(&buffer));
		if (bytes_read == 0)
			break ;
		temp_buffer[bytes_read] = '\0';
		buffer = ft_strjoin_free(buffer, temp_buffer);
		if (!buffer)
			return (small_clean(&temp_buffer));
		if (ft_strchr2(buffer, '\n'))
			break ;
	}
	free(temp_buffer);
	return (buffer);
}

static char	*extract_line(char **buffer)
{
	char	*line;
	int		i;
	int		new_line_flag;

	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	new_line_flag = 0;
	if ((*buffer)[i] == '\n')
		new_line_flag = 1;
	line = ft_calloc2(i + new_line_flag + 1, 1);
	if (!line)
		return (NULL);
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
	{
		line[i] = (*buffer)[i];
		i++;
	}
	if (new_line_flag)
		line[i] = '\n';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (small_clean(&buffer));
	buffer = read_to_buffer(fd, buffer);
	if (!buffer)
		return (small_clean(&buffer));
	line = extract_line(&buffer);
	if (!line)
		return (small_clean(&buffer));
	buffer = clean_buffer(buffer);
	return (line);
}
