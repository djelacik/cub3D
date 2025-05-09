/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_head.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 01:47:34 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/09 17:09:08 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

