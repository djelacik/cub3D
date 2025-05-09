/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algorithms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 02:01:28 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/09 17:13:08 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	check_cell_strict(t_data *data, int i, int j)
{
	char	**grid;
	char	*row;
	int	 h;

	grid = data->map.grid;
	row = grid[i];
	h = data->map.height;
	if (i == 0 || i == h - 1 || j == 0 || row[j + 1] == '\0')
	{
		return (row[j] == '1');
	}
	if (row[j] == '0' || row[j] == 'D')
	{
		return (grid[i][j - 1] != '\0' && grid[i - 1][j] != '\0'
			&& grid[i + 1][j] != '\0'&& row[j + 1] != '\0');
	}
	return (row[j] == '1');
}

bool	is_map_closed_strict(t_data *data)
{
	int	 i;
	int	 j;
	char	*row;

	i = 0;
	while (i < data->map.height)
	{
		row = data->map.grid[i];
		j = 0;
		while (row[j])
		{
			if (!check_cell_strict(data, i, j))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

//flood-fill from (i,j), returns false if any path leaks out
//uses visited array so we don't edit data->map.grid
//off top/bottom means open
//off left/right means open
//wall, this path is sealed
//already visited, sealed
//anything other than floor or door, treat as sealed
//recursively, if leaks out from anywhere propagate false
//mark visited
bool	flood_fill(t_data *data, bool **visited, int i, int j)
{
	char	**grid;
	int		len;

	grid = data->map.grid;
	if (i < 0 || i >= data->map.height)
		return (false);
	len = ft_strlen(grid[i]);
	if (j < 0 || j >= len)
		return (false);
	if (grid[i][j] == '1')
		return (true);
	if (visited[i][j])
		return (true);
	if (grid[i][j] != '0' && grid[i][j] != 'D')
		return (true);
	visited[i][j] = true;
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

bool **allocate_bool_array(t_data *data)
{
	int		height;
	char	**grid;
	bool	**visited;
	int		len;
	int		i;

	height = data->map.height;
	grid   = data->map.grid;
	visited = gc_alloc(sizeof(bool *) * height);
	if (!visited)
		return (false);
	i = 0;
	while (i < height)
	{
		len = ft_strlen(grid[i]);
		visited[i] = gc_alloc(sizeof(bool) * len);
		if (!visited[i])
			return (false);
		ft_memset(visited[i], 0, sizeof(bool) * len);
		i++;
	}
	return (visited);
}

bool	is_map_closed(t_data *data)
{
	int		start_i;
	int		start_j;
	bool	ok;
	bool	**visited;

	visited = allocate_bool_array(data);
	if (!visited)
		return (false);
	start_i = (int)(data->player.y - 0.5);
	start_j = (int)(data->player.x - 0.5);
	ok = flood_fill(data, visited, start_i, start_j);
	return (ok);
}
