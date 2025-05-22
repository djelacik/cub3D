/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:29:25 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/21 15:09:23 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	alloc_map_grid(t_data *data, size_t rows)
{
	data->map.height = rows;
	data->map.grid = gc_alloc((rows + 1) * sizeof(char *));
	if (!data->map.grid)
		error_return(data, "Map alloc failed");
	data->map.grid[rows] = NULL;
	return (false);
}

void	fill_grid_and_count(t_data *data, t_vec *map_vec, int *doors)
{
	size_t	i;
	char	**grid;
	int		j;
	int		len;

	grid = data->map.grid;
	i = 0;
	while (i < map_vec->len)
	{
		grid[i] = *(char **)vec_get(map_vec, i);
		len = ft_strlen(grid[i]);
		if (len > data->map.width)
			data->map.width = len;
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] == 'D')
				(*doors)++;
			j++;
		}
		i++;
	}
}

bool	alloc_doors_array(t_data *data, int doors)
{
	if (doors <= 0)
	{
		data->doors = NULL;
		return (false);
	}
	data->doors = gc_alloc(doors * sizeof(t_door));
	if (!data->doors)
		return (error_return(data, "Doors alloc failed"));
	ft_memset(data->doors, 0, doors * sizeof(t_door));
	return (false);
}

bool	build_map(t_data *data, t_vec *map_vec)
{
	int		doors;
	size_t	rows;

	doors = 0;
	rows = map_vec->len;
	if (alloc_map_grid(data, rows))
		return (true);
	fill_grid_and_count(data, map_vec, &doors);
	if (alloc_doors_array(data, doors))
		return (true);
	return (false);
}
