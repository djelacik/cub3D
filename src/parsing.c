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

bool	remove_spaces(char *line)
{
	char	*src;
	char	*dst;

	src = line;
	dst = line;
	while (*src)
	{
		if (*src != ' ' && *src != '\t')
			*dst++ = *src;
		src++;
	}
	*dst = '\0';
	return (true);
}

bool	parse_texture_line(const char *line, t_data *data)
{
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		//hardcoded jump of 2
		data->textures->north = mlx_load_png(line + 2);
		if (!data->textures->north)
		{
			ft_putstr_fd("Failed to load texture\n", 2);
			return (false);
		}
		return (true);
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		data->textures->south = mlx_load_png(line + 2);
		if (!data->textures->south)
		{
			ft_putstr_fd("Failed to load texture\n", 2);
			//free_textures
			return (false);
		}
		return (true);
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		data->textures->west = mlx_load_png(line + 2);
		if (!data->textures->west)
		{
			ft_putstr_fd("Failed to load texture\n", 2);
			//free_textures
			return (false);
		}
		return (true);
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		data->textures->east = mlx_load_png(line + 2);
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

//check commas and numbers
bool parse_color_values(char *str, t_color *color)
{
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
	if (line[0] == 'F')
	{
		//hardcoded jump of 1
		return parse_color_values(line + 1, &data->floor);
	}
	if (line[0] == 'C')
	{
		return parse_color_values(line + 1, &data->ceiling);
	}
	return false;
}

bool is_map_closed(t_data *data)
{
	int i, j;

	// Check first and last row
	for (j = 0; j < data->map.width; j++)
	{
		// If we are beyond row's length, we consider it 'space' => error
		if (j >= (int)ft_strlen(data->map.grid[0]) || data->map.grid[0][j] != '1')
			return (false);
		if (j >= (int)ft_strlen(data->map.grid[data->map.height - 1]) 
			|| data->map.grid[data->map.height - 1][j] != '1')
			return (false);
	}

	// Check left and right walls
	for (i = 1; i < data->map.height - 1; i++)
	{
		int len = (int)ft_strlen(data->map.grid[i]);
		if (len == 0)
			return (false);
		if (data->map.grid[i][0] != '1')
			return (false);
		// The last visible character in the row
		if (data->map.grid[i][len - 1] != '1')
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
	int	row_len;

	line = NULL;
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		perror("open failed");
		return (1);
	}
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
		//skip empty lines
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		nl = ft_strchr(line, '\n');
		if (nl)
			*nl = '\0';
		remove_spaces(line);
		printf("line->%s<-\n", line);
		/*
		if (is_map_line(line))
		{
			if (!map_started)
				map_started = true;
			printf("is map.grid line\n");
		}
		*/
		if (is_map_line(line))
		{
			if (!map_started)
				map_started = true;
			if (vec_push(&map_vec, &line) < 0)
			{
				ft_putstr_fd("Vec push failed\n", 2);
				free(line);
				status = 1;
				break ;
			}
		}
		/*
		else if (!map_started)
		{
			if (is_texture_line(line))
				printf("is texture line\n");
			if (is_color_line(line))
				printf("is color line\n");
		}
		*/
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
		/*
		else
			printf("error: either map.grid is not last or line not valid\n");
		*/
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
		data->map.height = map_vec.len;
		data->map.grid = malloc((map_vec.len + 1) * sizeof(char *));
		if (!data->map.grid)
		{
			ft_putstr_fd("Map alloc failed\n", 2);
			status = 1;
		}
		else
		{
			i = 0;
			while (i < map_vec.len)
			{
				data->map.grid[i] = *(char **)vec_get(&map_vec, i);
				row_len = ft_strlen(data->map.grid[i]);
				if (row_len > data->map.width)
					data->map.width = row_len;
				i++;
			}
			data->map.grid[map_vec.len] = NULL;
		}
	}
	/*
	if (!status && is_map_closed(data))
	{
		ft_putstr_fd("Map is not closed\n", 2);
		status = 1;
	}
	*/
	vec_free(&map_vec);
	return (status);
}