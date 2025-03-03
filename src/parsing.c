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
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D'); //door?
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

bool	is_number(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return false;
		str++;
	}
	return true;
}

//check commas and numbers
bool	parse_color_values(char *str, uint32_t *color)
{
	int count;
	char **split;
	char **copy;
	int number;

	split = ft_split(str, ',', &count);
	if (count != 3)
		return (false);
	copy = split;
	while (*copy)
	{
		number = ft_atoi(*copy);
		if (!is_number(*copy) || number < 0 || number > 255)
			return (false);
		copy++;
	}
	/*
	color->r = ft_atoi(split[0]);
	color->g = ft_atoi(split[1]);
	color->b = ft_atoi(split[2]);
	color->a = 255;
	printf("color->r = %d\n", color->r);
	printf("color->g = %d\n", color->g);
	printf("color->b = %d\n", color->b);
	*/
	*color = get_rgba(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]), 255);
	return (true);
}

bool	parse_color_line(char *line, t_data *data)
{
	bool	status;
	if (line[0] == 'F')
	{
		//hardcoded jump of 1
		printf("Floor color:\n");
		status = parse_color_values(line + 1, &data->floor);
		printf("data->floor_color = 0x%08x\n", data->floor);
		return (status);
	}
	if (line[0] == 'C')
	{
		//hardcoded jump of 1
		printf("Ceiling color:\n");
		status = parse_color_values(line + 1, &data->ceiling);
		printf("data->ceiling_color = 0x%08x\n", data->ceiling);
		return (status);
	}
	return false;
}

//not working!!!
bool	parse_player_pos(t_data *data)
{
	int i, j, already_assigned = 0;

	i = 0;
	while (data->map.grid[i])
	{
		j = 0;
		while (data->map.grid[i][j])
		{
			if ((data->map.grid[i][j] == 'N' || data->map.grid[i][j] == 'S' || data->map.grid[i][j] == 'E' || data->map.grid[i][j] == 'W') && !already_assigned)
			{
				/*
				if (data->map.grid[i][j] == 'N')
					data->player.angle = 270 * DEGREE;
				else if (data->map.grid[i][j] == 'S')
					data->player.angle = 90 * DEGREE;
				else if (data->map.grid[i][j] == 'E')
					data->player.angle = 0;
				else if (data->map.grid[i][j] == 'W')
					data->player.angle = 180 * DEGREE;
				*/
				data->player.x = j + 0.5;
				data->player.y = i + 0.5;
				//printf("--->%c becomes ", data->map.grid[i][j]);
				data->map.grid[i][j] = '0';
				//printf("%c<---\n", data->map.grid[i][j]);
				already_assigned = 1;
			}
			else if((data->map.grid[i][j] == 'N' || data->map.grid[i][j] == 'S' || data->map.grid[i][j] == 'E' || data->map.grid[i][j] == 'W') && already_assigned)
			{
				ft_putstr_fd("Error, multiple player positions\n", 2);
				return (true);
			}
			else if (data->map.grid[i][j] == 'D')
			{

				data->doors[data->door_count].x = j;
				data->doors[data->door_count].y = i;
				data->doors[data->door_count].state = CLOSED;
				data->doors[data->door_count].progress = 0;
			}
			else if (data->map.grid[i][j] != '0' && data->map.grid[i][j] != '1')
			{
				ft_putstr_fd("Error, invalid character in map\n", 2);
				return (true);
			}
			j++;
		}
		i++;
	}
	if (!already_assigned)
	{
		ft_putstr_fd("Error, no player position found\n", 2);
		return (true);
	}
	return (false);
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
	data->player.angle = 0;
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
		//printf("line->%s<-\n", line);
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
				printf("->%s<-\n", data->map.grid[i]);
				/*should this be here?*/
				int j = 0;
				while (data->map.grid[i][j])
				{
					if (data->map.grid[i][j] == 'D')
					{
						data->door_count++;
					}
					/*
					else if (data->map.grid[i][j] == 'X')
					{
						//data->enemy_count++;
					}
					*/
					j++;
				}
				/*should this be here?*/
				row_len = ft_strlen(data->map.grid[i]);
				if (row_len > data->map.width)
					data->map.width = row_len;
				i++;
			}
			data->doors = malloc(data->door_count * sizeof(t_door));
			data->map.grid[map_vec.len] = NULL;
		}
	}
	if (!status)
	{
		if (parse_player_pos(data))
			status = 1;
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