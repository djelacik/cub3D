/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:32:54 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/21 13:44:30 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	push_map_line(t_vec *map_vec, char *line, t_data *data)
{
	if (vec_push(map_vec, &line) < 0)
		return (error_return(data, "Vec push failed"));
	return (0);
}

bool	categorize_line(t_data *data, char *line, t_vec *map_vec, bool *m_s)
{
	if (is_map_line(line) && !line_is_only_spaces(line))
	{
		if (!data->f_color_found || !data->c_color_found
			|| !textures_ready(data))
		{
			data->error_msg = "Please define colors/textures before the map";
			return (true);
		}
		*m_s = true;
		if (push_map_line(map_vec, line, data))
			return (true);
	}
	else if (!*m_s)
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

bool	parse_file_lines(int fd, t_data *data, t_vec *map_vec, bool *m_s)
{
	char	*line;
	char	*nl;
	bool	error;

	error = 0;
	line = gc_next_line(fd, READ_LINE);
	while (line)
	{
		if (line[0] == '\n' && !*m_s)
		{
			line = gc_next_line(fd, READ_LINE);
			continue ;
		}
		nl = ft_strchr(line, '\n');
		if (nl)
			*nl = '\0';
		error = categorize_line(data, line, map_vec, m_s);
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

	fd = open_cub_file(filepath);
	if (fd < 0)
		return (error_return(data, "Open failed"));
	if (vec_new(&data->map_vec, VEC_INIT_SIZE, sizeof(char *)) < 0)
	{
		close_cub_file(fd, data);
		return (error_return(data, "Vec alloc failed"));
	}
	if (parse_file_lines(fd, data, &data->map_vec, &data->map_started))
	{
		close_cub_file(fd, data);
		return (1);
	}
	close_cub_file(fd, data);
	if (build_map(data, &data->map_vec))
		return (error_return(data, "Map build failed"));
	if (parse_player_pos(data))
		return (error_return(data, "Player position not found"));
	if (data->strict && !is_map_closed_strict(data))
		return (error_return(data, "Map is open (strict checking)"));
	else if (!is_map_closed(data))
		return (error_return(data, "Map is open"));
	return (0);
}
