/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:34:31 by djelacik          #+#    #+#             */
/*   Updated: 2025/05/21 14:53:45 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	get_map_cell(t_data *data, double x, double y)
{
	int	xi;
	int	yi;

	xi = (int)x;
	yi = (int)y;
	if (yi < 0 || yi >= data->map.height)
		return ('1');
	if (xi < 0 || xi >= (int)ft_strlen(data->map.grid[yi]))
		return ('1');
	return (data->map.grid[yi][xi]);
}

// If door is closed or only partially open, consider it a wall
bool	is_wall(t_data *data, double x, double y)
{
	char	cell;
	int		i;

	cell = get_map_cell(data, x, y);
	if (cell == '1')
		return (1);
	else if (cell == 'D')
	{
		i = 0;
		while (i < data->door_count)
		{
			if (data->doors[i].x == (int)x && data->doors[i].y == (int)y)
			{
				if (data->doors[i].state == CLOSED
					|| data->doors[i].progress < 0.8)
					return (true);
				else
					return (false);
			}
			i++;
		}
		return (true);
	}
	return (false);
}

int	can_move_to(t_data *data, double new_x, double new_y)
{
	double	diag_offset;

	diag_offset = COLLISION_LIMIT / sqrt(2);
	if (is_wall(data, new_x + COLLISION_LIMIT, new_y))
		return (0);
	if (is_wall(data, new_x - COLLISION_LIMIT, new_y))
		return (0);
	if (is_wall(data, new_x, new_y + COLLISION_LIMIT))
		return (0);
	if (is_wall(data, new_x, new_y - COLLISION_LIMIT))
		return (0);
	if (is_wall(data, new_x + diag_offset, new_y + diag_offset))
		return (0);
	if (is_wall(data, new_x - diag_offset, new_y + diag_offset))
		return (0);
	if (is_wall(data, new_x + diag_offset, new_y - diag_offset))
		return (0);
	if (is_wall(data, new_x - diag_offset, new_y - diag_offset))
		return (0);
	return (1);
}
