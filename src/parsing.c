/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 09:32:54 by aapadill          #+#    #+#             */
/*   Updated: 2025/02/21 15:27:09 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <fcntl.h>

//is_map_line()
//parse_texture_line()
//parse_color_line()
//is_map_closed()

static bool	valid_character(char c)
{
	return (c == ' ' || c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

bool	is_map_line(char *line)
{
	while (*line)
	{
		if (!valid_character(*line))
			return (false);
		line++;
	}
	return (true);
}

bool	parse_texture_line(const char *line, t_data *data)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		//data->textures.north = ft_strdup(line + 3);
		//hardcoded jump of 3 //make it to jump spaces
		data->textures->north = mlx_load_png(line + 3);
		if (!data->textures->north)
		{
			ft_putstr_fd("Failed to load texture\n", 2);
			return (false);
		}
		return (true);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		data->textures->south = mlx_load_png(line + 3);
		if (!data->textures->south)
		{
			ft_putstr_fd("Failed to load texture\n", 2);
			//free_textures
			return (false);
		}
		return (true);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		data->textures->west = mlx_load_png(line + 3);
		if (!data->textures->west)
		{
			ft_putstr_fd("Failed to load texture\n", 2);
			//free_textures
			return (false);
		}
		return (true);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		data->textures->east = mlx_load_png(line + 3);
		if (!data->textures->east)
		{
			ft_putstr_fd("Failed to load texture\n", 2);
			//free_textures
			return (false);
		}
		return (true);
	}
	return (false);
}

bool parse_color_values(char *str, t_color *color)
{
	// skip leading spaces
	while (*str == ' ' || *str == '\t')
		str++;
	// now str should be "220,100,0" or something similar
	int r, g, b;
	if (sscanf(str, "%d,%d,%d", &r, &g, &b) != 3)
		return false;
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return false;
	color->r = r;
	color->g = g;
	color->b = b;
	color->a = 255;
	return true;
}

bool	parse_color_line(char *line, t_data *data)
{
	if (line[0] == 'F' && (line[1] == ' ' || line[1] == '\t'))
	{
		// parse after 'F '
		return parse_color_values(line + 1, &data->floor);
	}
	if (line[0] == 'C' && (line[1] == ' ' || line[1] == '\t'))
	{
		// parse after 'C '
		return parse_color_values(line + 1, &data->ceiling);
	}
	return false;
}

bool is_map_closed(t_data *data)
{
	int i, j;

	// Check first and last row
	for (j = 0; j < data->width; j++)
	{
		// If we are beyond row's length, we consider it 'space' => error
		if (j >= (int)ft_strlen(data->map[0]) || data->map[0][j] != '1')
			return (false);
		if (j >= (int)ft_strlen(data->map[data->height - 1]) 
			|| data->map[data->height - 1][j] != '1')
			return (false);
	}

	// Check left and right walls
	for (i = 1; i < data->height - 1; i++)
	{
		int len = (int)ft_strlen(data->map[i]);
		if (len == 0)
			return (false);
		if (data->map[i][0] != '1')
			return (false);
		// The last visible character in the row
		if (data->map[i][len - 1] != '1')
			return (false);
	}
	return (true);
}


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
	//data->textures->north = NULL;
	//data->textures->south = NULL;
	//data->textures->west  = NULL;
	//data->textures->east  = NULL;
	//data->floor_color = (t_color){ -1, -1, -1 };
	//data->ceiling_color = (t_color){ -1, -1, -1 };
	data->map = NULL;
	//data->height = 0;
	//data->width = 0;

	t_vec	map_vec;
	if (vec_new(&map_vec, 16, sizeof(char *)) < 0)
	{
		ft_putstr_fd("Vec alloc failed\n", 2);
		close(fd);
		return (1);
	}
	line = get_next_line(fd);
	while (line)
	{
		printf("line: %s\n", line);
		printf("map_started?: %i\n", map_started);
		//remove nl
		if (!*line)
			break ;
		nl = ft_strchr(line, '\n');
		if (nl)
			*nl = '\0';
		//skip empty lines
		if (!map_started && !*line)
		{
			//free(line);
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
			//printf("so this should happen: %s\n", line);
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
			free(line);
			status = 1;
			break ;
		}
		line = get_next_line(fd);
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
	/* 
	//hardcoded //check all bytes of color struct
	if (data->floor.r < 0 || data->ceiling.r < 0)
	{
		ft_putstr_fd("Invalid colors\n", 2);
		status = 1;
	}
	*/
	if (!status && is_map_closed(data))
	{
		ft_putstr_fd("Map is not closed\n", 2);
		status = 1;
	}
	vec_free(&map_vec);
	return (status);
}