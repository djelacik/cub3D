/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:32:54 by aapadill          #+#    #+#             */
/*   Updated: 2025/04/03 09:29:49 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int  init_map_vector(t_vec *vec)
{
    if (vec_new(vec, VEC_INIT_SIZE, sizeof(char *)) < 0)
        return (-1);
    return (0);
}

int  push_map_line(t_vec *map_vec, char *line, t_data *data)
{
    if (vec_push(map_vec, &line) < 0)
    {
        data->error_msg = "Vec push failed";
        return (1);
    }
    return (0);
}

bool categorize_line(t_data *data, char *line, t_vec *map_vec, bool *map_started)
{
	if (is_map_line(line) && !line_is_only_spaces(line))
	{
		if (!data->f_color_found || !data->c_color_found || !textures_ready(data))
		{
			data->error_msg = "Please define colors/textures before the map";
			return (true);
		}
		*map_started = true;
		if (push_map_line(map_vec, line, data))
			return (true);
	}
	else if (!*map_started)
	{
		if (process_header_line(line, data))
			return (true);
	}
	else
	{
		data->error_msg = "Map must be last in file";
		return (true);
	}
	return (false);
}

bool	parse_file_lines(int fd, t_data *data, t_vec *map_vec, bool *map_started)
{
	char	*line;
	char	*nl;
	bool	error;

	error = 0;
	// line = NULL;
	line = gc_next_line(fd, READ_LINE);
	while (line)
	{
		if (line[0] == '\n' && !*map_started)
		{
			line = gc_next_line(fd, READ_LINE);
			continue ;
		}
		nl = ft_strchr(line, '\n');
		if (nl)
			*nl = '\0';
		error = categorize_line(data, line, map_vec, map_started);
		if (error)
			break ;
		line = gc_next_line(fd, READ_LINE);
	}
	gc_next_line(fd, CLEAN_LINE);
	return (error);
}

int	parse_cubfile(char *filepath, t_data *data)
{
	int		fd;
	bool	map_started;
	t_vec	map_vec;

	map_started = false;
	fd = open_cub_file(filepath);
	if (fd < 0)
	{
		data->error_msg = "Open failed";
		return (1);
	}
	if (init_map_vector(&map_vec) < 0)
	{
		data->error_msg = "Vec alloc failed";
		close_cub_file(fd, data);
		return (1);
	}
	if (parse_file_lines(fd, data, &map_vec, &map_started))
	{
		close_cub_file(fd, data);
		return (1);
	}
	if (build_map(data, &map_vec))
	{
		data->error_msg = "Map build failed";
		return (1);
	}
	if (parse_player_pos(data))
	{
		data->error_msg = "Player position not found";
		return (1);
	}
	if (data->strict && !is_map_closed_strict(data))
	{
		data->error_msg = "Map is open (strict checking)";
		return (1);
	}
	else if (!is_map_closed(data))
	{
		data->error_msg = "Map is open";
		return (1);
	}
	return (0);
}
