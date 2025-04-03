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
#include <fcntl.h>

static bool	valid_character(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == 'D');
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

bool	load_texture(char *path, mlx_texture_t **texture)
{
	*texture = mlx_load_png(path);
	if (!*texture)
	{
		ft_putstr_fd("Failed to load texture\n", 2);
		return (false);
	}
	return (true);
}

bool	parse_texture_line(char *line, t_data *data)
{
	t_textures		*t;

	t = data->textures;
	if (!ft_strncmp(line, "NO", 2) && !t->north)
		return (load_texture(line + 2, &t->north));
	else if (!ft_strncmp(line, "SO", 2)  && !t->south)
		return (load_texture(line + 2, &t->south));
	else if (!ft_strncmp(line, "WE", 2) && !t->west)
		return (load_texture(line + 2, &t->west));
	else if (!ft_strncmp(line, "EA", 2) && !t->east)
		return (load_texture(line + 2, &t->east));
	return (false);
}

bool	textures_ready(t_data *data)
{
	t_textures		*t;

	t = data->textures;
	return (t->north && t->south && t->west && t->east);
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
	*color = get_rgba(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]), 255);
	return (true);
}

bool	parse_color_line(char *line, t_data *data)
{
	bool	status;
	if (!data->f_color_found && line[0] == 'F')
	{
		//hardcoded jump of 1
		printf("Floor color:\n");
		status = parse_color_values(line + 1, &data->floor);
		printf("data->floor_color = 0x%08x\n", data->floor);
		if (status)
			data->f_color_found = 1;
		return (status);
	}
	if (!data->c_color_found && line[0] == 'C')
	{
		//hardcoded jump of 1
		printf("Ceiling color:\n");
		status = parse_color_values(line + 1, &data->ceiling);
		printf("data->ceiling_color = 0x%08x\n", data->ceiling);
		if (status)
			data->c_color_found = 1;
		return (status);
	}
	return false;
}

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
				if (data->map.grid[i][j] == 'N')
					data->player.angle = 3 * M_PI / 2; // 270 degrees
				else if (data->map.grid[i][j] == 'S')
					data->player.angle = M_PI / 2; // 90 degrees
				else if (data->map.grid[i][j] == 'E')
					data->player.angle = 0;
				else if (data->map.grid[i][j] == 'W')
					data->player.angle = M_PI;
				data->player.x = j + 0.5;
				data->player.y = i + 0.5;
				data->map.grid[i][j] = '0';
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
				data->door_count++;
			}
			//neccessary?
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
	int i, j, line_len;
	int height = data->map.height;
	i = 0;
	line_len = 0;

	while (i < height)
	{
		j = 0;
		line_len = ft_strlen(data->map.grid[i]);
		//printf("%i has %i chars---->", i, line_len);
		while (j < line_len)
		{
			if (i == 0 || i == height - 1 || j == 0 || j == line_len - 1)
			{
				if (data->map.grid[i][j] != '1')
				{
					ft_putstr_fd("Error, map is not closed\n", 2);
					return (false);
				}
			}
			else if (data->map.grid[i][j] == '0' || data->map.grid[i][j] == 'D')
			{
				if (data->map.grid[i - 1][j] == '\0' || data->map.grid[i + 1][j] == '\0' || data->map.grid[i][j - 1] == '\0' || data->map.grid[i][j + 1] == '\0')
				{
					ft_putstr_fd("Error, map is not closed (intermediate)\n", 2);
					return (false);
				}
			}
			else
			{
				if (data->map.grid[i][j] != '1')
				{
					ft_putstr_fd("Error, map is not closed\n", 2);
					return (false);
				}
			}
			/*
			if (data->map.grid[i][j] != '\0')
				printf("%c", data->map.grid[i][j]);
			else
				printf("X");
			*/
			j++;
		}
		//printf("<----\n");
		i++;
	}
	return true;
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

	line = NULL;
	data->player.angle = 0;
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
	{
		perror("open failed");
		return (1);
	}
	t_vec	map_vec;
	if (vec_new(&map_vec, VEC_INIT_SIZE, sizeof(char *)) < 0)
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
			if (!data->f_color_found || !data->c_color_found || !textures_ready(data))
			{
				ft_putstr_fd("You're trying to initialize map before colors or textures, exiting\n", 2);
				status = 1;
				break ;
			}
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
				ft_putstr_fd("Either some invalid line or trying to define the same thing twice\n", 2);
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
				//printf("->%s<-\n", data->map.grid[i]);
				/*should this be here?*/
				int j = 0;
				while (data->map.grid[i][j])
				{
					if (data->map.grid[i][j] == 'D')
					{
						doors_count++;
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
			data->doors = malloc(doors_count * sizeof(t_door));
			ft_memset(data->doors, 0, doors_count * sizeof(t_door));
			data->map.grid[map_vec.len] = NULL;
		}
	}
	if (!status)
	{
		status = parse_player_pos(data);
	}
	if (!status && !is_map_closed(data))
	{
		i = 0;
		while (i < map_vec.len)
		{
			printf("->%s<-\n", data->map.grid[i]);
			i++;
		}
		ft_putstr_fd("Map is not closed\n", 2);
		status = 1;
	}
	vec_free(&map_vec);
	printf("reached end of parsing\n");
	return (status);
}
