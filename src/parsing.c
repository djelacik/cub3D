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

//*key and *rest point at new malloc strings
static bool split_line(char *line, char **key, char **rest)
{
	char	*trimmed;
	char	*sep;

	trimmed = gc_strtrim(line, " \t\n\r");
	if (!trimmed)
		return (false);
	sep = trimmed;
	//find the first space, that will be our separator
	while (*sep && !ft_isspace(*sep))
		sep++;
	if (!*sep)
		return (false);
	*sep = '\0';
	sep++;
	//skip spaces before the rest
	while (ft_isspace(*sep))
		sep++;
	if (!*sep)
		return (false);
	*key = gc_strdup(trimmed);
	*rest = gc_strtrim(sep, " \t\n\r");
	return (*key && *rest);
}

bool	parse_color_values(char *str, uint32_t *color)
{
	int count;
	char **vals;
	int i;
	int nums[3];

	if (count_char(str, ',') != 2)
		return (false);
	vals = gc_split(str, ',', &count);
	if (!vals || count != 3)
		return (false);
	i = 0;
	while (i < 3)
	{
		vals[i] = gc_strtrim(vals[i], " \t\n\r");
		if (!is_number(vals[i]))
			return (false);
		nums[i] = ft_atoi(vals[i]);
		if (nums[i] < 0 || nums[i] > 255)
			return (false);
		i++;
	}
	*color = get_rgba(nums[0], nums[1], nums[2], 255);
	return (true);
}

//(F | C) <r,g,b>
bool	parse_color_line(char *line, t_data *data)
{
	char	*key;
	char	*vals;
	bool	status;

	status = false;
	if (!split_line(line, &key, &vals))
		return (false);
	if (!ft_strncmp(key, "F", 2) && !data->f_color_found)
	{
		status = parse_color_values(vals, &data->floor);
		if (status)
			data->f_color_found = true;
	}
	else if (!ft_strncmp(key, "C", 2) && !data->c_color_found)
	{
		status = parse_color_values(vals, &data->ceiling);
		if (status)
			data->c_color_found = true;
	}
	//gc_free(key);
	//gc_free(vals);
	return (status);
}

//(NO | SO | WE | EA) <path>
bool	parse_texture_line(char *line, t_data *data)
{
	char		*key;
	char		*path;
	bool		ok;
	t_textures	*t;

	ok = false;
	t = data->textures;
	if (!split_line(line, &key, &path))
		return (false);
	if (!ft_strncmp(key, "NO", 3) && !t->north)
		ok = load_texture(path, &t->north);
	else if (!ft_strncmp(key, "SO", 3) && !t->south)
		ok = load_texture(path, &t->south);
	else if (!ft_strncmp(key, "WE", 3) && !t->west)
		ok = load_texture(path, &t->west);
	else if (!ft_strncmp(key, "EA", 3) && !t->east)
		ok = load_texture(path, &t->east);
	else if (!ft_strncmp(key, "DO", 3) && !t->door)
		ok = load_texture(path, &t->door);
	gc_free(key);
	gc_free(path);
	return (ok);
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
				data->error_msg = "Multiple player positions detected";
				return (true);
			}
			else if (data->map.grid[i][j] == 'D')
			{
				if (data->textures->door == NULL)
				{
					data->error_msg = "Door texture not defined";
					return (true);
				}
				data->doors[data->door_count].x = j;
				data->doors[data->door_count].y = i;
				data->doors[data->door_count].state = CLOSED;
				data->doors[data->door_count].progress = 0;
				data->door_count++;
			}
			else if (data->map.grid[i][j] == ' ')
			{
				data->map.grid[i][j] = '0';
			}
			else if (data->map.grid[i][j] != '0' && data->map.grid[i][j] != '1')
			{
				data->error_msg = "Invalid character in map";
				return (true);
			}
			j++;
		}
		i++;
	}
	if (!already_assigned)
	{
		data->error_msg = "No player position found";
		return (true);
	}
	return (false);
}

bool is_map_closed_strict(t_data *data)
{
	int i, j, line_len;
	int height = data->map.height;
	i = 0;
	line_len = 0;

	while (i < height)
	{
		j = 0;
		line_len = ft_strlen(data->map.grid[i]);
		while (j < line_len)
		{
			if (i == 0 || i == height - 1 || j == 0 || j == line_len - 1)
			{
				if (data->map.grid[i][j] != '1')
				{
					return (false);
				}
			}
			else if (data->map.grid[i][j] == '0' || data->map.grid[i][j] == 'D')
			{
				if (data->map.grid[i - 1][j] == '\0' || data->map.grid[i + 1][j] == '\0' || data->map.grid[i][j - 1] == '\0' || data->map.grid[i][j + 1] == '\0')
				{
					return (false);
				}
			}
			else
			{
				if (data->map.grid[i][j] != '1')
				{
					return (false);
				}
			}
			j++;
		}
		i++;
	}
	return true;
}

//flood-fill from (i,j), returns false if any path leaks out
//uses visited array so we don't edit data->map.grid
static bool	flood_fill(t_data *data, bool **visited, int i, int j)
{
	char	**grid;
	int		height;
	int		len;

	grid   = data->map.grid;
	height = data->map.height;
	//off top/bottom means open
	if (i < 0 || i >= height)
		return (false);
	//off left/right means open
	len = ft_strlen(grid[i]);
	if (j < 0 || j >= len)
		return (false);
	//wall, this path is sealed
	if (grid[i][j] == '1')
		return (true);
	//already visited, sealed
	if (visited[i][j])
		return (true);
	//anything other than floor or door, treat as sealed
	if (grid[i][j] != '0' && grid[i][j] != 'D')
		return (true);
	//mark visited
	visited[i][j] = true;
	//recursively, if leaks out from anywhere propagate false
	if (!flood_fill(data, visited, i - 1, j))
		return (false);
	if (!flood_fill(data, visited, i + 1, j))
		return (false);
	if (!flood_fill(data, visited, i, j - 1))
		return (false);
	if (!flood_fill(data, visited, i, j + 1))
		return (false);
	return (true);
}

bool	is_map_closed(t_data *data)
{
	int		height;
	char	**grid;
	bool	**visited;
	int		i;
	int		len;
	int		start_i;
	int		start_j;
	bool	ok;

	height = data->map.height;
	grid   = data->map.grid;
	//allocate visited (bool) array
	visited = malloc(sizeof(bool *) * height);
	if (!visited)
		return (false);
	i = 0;
	while (i < height)
	{
		len = ft_strlen(grid[i]);
		visited[i] = malloc(sizeof(bool) * len);
		if (!visited[i])
			return (false);
		ft_memset(visited[i], 0, sizeof(bool) * len);
		i++;
	}
	//starting cell from player position
	start_i = (int)(data->player.y - 0.5);
	start_j = (int)(data->player.x - 0.5);
	ok = flood_fill(data, visited, start_i, start_j);
	//free visited
	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
	return (ok);
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
	fd = open(filepath, O_RDONLY); //check more errors
	if (fd < 0)
	{
		perror("open failed");
		return (1);
	}
	t_vec	map_vec;
	if (vec_new(&map_vec, VEC_INIT_SIZE, sizeof(char *)) < 0)
	{
		//ft_putstr_fd("Vec alloc failed\n", 2);
		data->error_msg = "Vec alloc failed";
		close(fd);
		return (1);
	}
	line = gc_next_line(fd, READ_LINE);
	while (line)
	{
		//skip empty lines
		if (line[0] == '\n' && !map_started)
		{
			//free(line);
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
			if (!map_started)
				map_started = true;
			if (vec_push(&map_vec, &line) < 0)
			{
				data->error_msg = "Vec push failed";
				status = 1;
				break ;
			}
		}
		else if (!map_started)
		{
			//remove_spaces(line);
			if (!parse_texture_line(line, data) && !parse_color_line(line, data))
			{
				data->error_msg = "Check your color/textures";
				status = 1;
				break ;
			}
		}
		else
		{
			data->error_msg = "Map must be the last thing in file";
			status = 1;
			break ;
		}
		line = gc_next_line(fd, READ_LINE);
	}
	gc_next_line(fd, CLEAN_LINE);
	close(fd);
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