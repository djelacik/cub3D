/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:32:54 by aapadill          #+#    #+#             */
/*   Updated: 2025/02/21 14:55:13 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//is_map_line()
//parse_texture_line()
//parse_color_line
//is_map_closed()

int	parse_cubfile(char *filepath, t_data *data)
{
	char	*line;
	char	*nl;
	int		fd;
	bool	map_started = false;
	bool	status = 0;
	size_t	i;
	int		row_len;

	line = NULL;
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		perror("open failed");
		return (1);
	}
	//memset 0 data->(everything)
	data->textures->north = NULL;
	data->textures->south = NULL;
	data->textures->west  = NULL;
	data->textures->east  = NULL;
	//data->floor_color = (t_color){ -1, -1, -1 };
	//data->ceiling_color = (t_color){ -1, -1, -1 };
	data->map = NULL;
	data->height = 0;
	data->width = 0;

	t_vec	map_vec;
	if (vec_new(&map_vec, 16, sizeof(char *) < 0))
	{
		ft_putstr_fd("Vec alloc failed\n", 2);
		close(fd);
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		//remove nl
		nl = ft_strchr(line, '\n');
		if (nl)
			*nl = '\0';
		//skip empty lines
		if (!map_started && *line == '\0')
		{
			free(line);
			continue ;
		}
		//if line has valid map chars, add it to map_vec
		if (is_map_line(line))
		{
			map_started = true;
			if (vec_push(&map_vec, &line) < 0)
			{
				ft_putstr_fd("Vec push failed\n", 2);
				free(line);
				status = 1;
				break ;
			}
		}
		//if line doesnt look like map stuff, might be either texture or color
		else if (!map_started)
		{
			if (!parse_texture_line(line, data) && !parse_color_line(line, data))
			{
				ft_putstr_fd("Invalid config line\n", 2);
				free(line);
				status = 1;
				break ;
			}
		}
		//map already started but not map_line
		else
		{
			ft_putstr_fd("Map must be the last thing in file\n", 2);
			//print line
			free(line);
			status = 1;
			break ;
		}
	}
	close(fd);
	//clean static buffer from gnl
	if (!status)
	{
		//create map struct? with map.height, map.width, map.grid
		data->height = map_vec.len;
		data->map = malloc((map_vec.len + 1) * sizeof(char *));
		if (!data->map)
		{
			ft_putstr_fd("Map alloc failed\n", 2);
			status = 1;
		}
		//malloc worked
		else
		{
			i = 0;
			while (i < map_vec.len)
			{
				data->map[i] = *(char **)vec_get(&map_vec, i);
				row_len = (int)ft_strlen(data->map[i]);
				if (row_len > data->width)
					data->width = row_len;
				i++;
			}
			data->map[map_vec.len] = NULL;
		}
	}
	if (!data->textures->north || !data->textures->south || !data->textures->east || data->textures->west)
	{
		ft_putstr_fd("Missing one or more texture paths\n", 2);
		status = 1;
	}
	//hardcoded
	if (data->floor_color < 0 || data->ceiling_color < 0)
	{
		ft_putstr_fd("Invalid colors\n", 2);
		status = 1;
	}
	if (!status && is_map_closed(&data->map))
	{
		ft_putstr_fd("Map is not closed\n", 2);
		status = 1;
	}
	vec_free(&map_vec);
}
