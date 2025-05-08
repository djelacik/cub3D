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

int  open_cub_file(const char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (-1);
    return (fd);
}

int  close_cub_file(int fd)
{
	if (close(fd) < 0)
		return (-1);
	return (0);
}

int  init_map_vector(t_vec *vec)
{
    if (vec_new(vec, VEC_INIT_SIZE, sizeof(char *)) < 0)
        return (-1);
    return (0);
}

int  process_header_line(char *line, t_data *data)
{
    if (!parse_texture_line(line, data)
        && !parse_color_line(line, data))
    {
        data->error_msg = "Invalid color/texture definition";
        return (1);
    }
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

int	parse_cubfile(char *filepath, t_data *data)
{
	char	*line;
	char	*nl;
	int		fd;
	bool	map_started = false;
	bool	status = 0;
	size_t	i;
	int	row_len;
	int		doors_count = 0;
	t_vec	map_vec;

	line = NULL;
	// fd = open(filepath, O_RDONLY); //check more errors
	// if (fd < 0)
	// {
	// 	perror("open failed");
	// 	return (1);
	// }
	fd = open_cub_file(filepath);
	if (fd < 0)
	{
		data->error_msg = "open failed";
		return (1);
	}
	if (init_map_vector(&map_vec) < 0)
	{
		data->error_msg = "Vec alloc failed";
		close(fd);
		return (1);
	}
	// if (vec_new(&map_vec, VEC_INIT_SIZE, sizeof(char *)) < 0)
	// {
	// 	//ft_putstr_fd("Vec alloc failed\n", 2);
	// 	data->error_msg = "Vec alloc failed";
	// 	close(fd);
	// 	return (1);
	// }
	line = gc_next_line(fd, READ_LINE);
	while (line)
	{
		if (line[0] == '\n' && !map_started)
		{
			line = gc_next_line(fd, READ_LINE);
			continue ;
		}
		nl = ft_strchr(line, '\n');
		if (nl)
			*nl = '\0';
		if (is_map_line(line) && !line_is_only_spaces(line))
		{
			if (!data->f_color_found || !data->c_color_found || !textures_ready(data))
			{
				data->error_msg = "Please define colors/textures before the map";
				status = 1;
				break ;
			}
			//if (!map_started)
			map_started = true;
			if (push_map_line(&map_vec, line, data))
			{
				status = 1;
			//	break ;
			}
		}
		else if (!map_started)
		{
			if (process_header_line(line, data))
			{
				status = 1;
				//break ;
			}
		}
		else
		{
			data->error_msg = "Map must be last in file";
			status = 1;
			//break ;
		}
		if (status)
			break ;
		line = gc_next_line(fd, READ_LINE);
	}
	gc_next_line(fd, CLEAN_LINE);
	if (close_cub_file(fd) < 0)
	{
		data->error_msg = "close failed";
		status = 1;
	}
	/*
	
	PAUSE HEREEEEEEE
	
	*/
	if (!status)
	{
		data->map.height = map_vec.len;
		data->map.grid = gc_alloc((map_vec.len + 1) * sizeof(char *));
		if (!data->map.grid)
		{
			data->error_msg = "Map alloc failed";
			status = 1;
		}
		else
		{
			i = 0;
			while (i < map_vec.len)
			{
				data->map.grid[i] = *(char **)vec_get(&map_vec, i);
				/*should this be here?*/
				int j = 0;
				while (data->map.grid[i][j])
				{
					if (data->map.grid[i][j] == 'D')
					{
						doors_count++;
					}
					j++;
				}
				/*should this be here?*/
				row_len = ft_strlen(data->map.grid[i]);
				if (row_len > data->map.width)
					data->map.width = row_len;
				i++;
			}
			if (doors_count > 0)
			{
				data->doors = gc_alloc(doors_count * sizeof(t_door));
				ft_memset(data->doors, 0, doors_count * sizeof(t_door));
			}
			else
			{
				data->doors = NULL;
			}
			data->map.grid[map_vec.len] = NULL;
		}
	}
	if (!status)
	{
		status = parse_player_pos(data);
	}
	if (!status)
	{
		if (data->strict)
		{
			if (!is_map_closed_strict(data))
			{
				data->error_msg = "Map is open (strict checking)";
				status = 1;
			}
		}
		else
		{
			if (!is_map_closed(data))
			{
				data->error_msg = "Map is open";
				status = 1;
			}
		}
	}
	vec_free(&map_vec);
	//printf("reached end of parsing\n");
	return (status);
}
