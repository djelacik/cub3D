/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_algorithms.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 02:01:28 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/08 02:01:29 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
bool	flood_fill(t_data *data, bool **visited, int i, int j)
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
