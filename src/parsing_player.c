/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:34:59 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/08 14:34:59 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
