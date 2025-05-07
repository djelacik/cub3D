/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 01:47:34 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/08 01:47:35 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
