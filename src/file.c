/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:23:26 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/21 15:04:27 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	open_cub_file(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	close_cub_file(int fd, t_data *data)
{
	if (close(fd) < 0)
	{
		data->error_msg = "Close failed";
		return (1);
	}
	return (0);
}

bool	has_cub_extension(char *filename)
{
	int	len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	return (ft_strncmp(filename + len - 4, ".cub", 4) == 0);
}
