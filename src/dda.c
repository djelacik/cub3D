/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:58:08 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/09 17:06:01 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	calc_delta(double dir)
{
	if (dir == 0.0)
		return (1e30);
	return (fabs(1.0 / dir));
}

void	init_dda_axis_x(t_data *data, t_dda *dda, double px, int mx)
{
	dda->delta_x = calc_delta(data->ray.dir_x);
	if (data->ray.dir_x < 0)
	{
		dda->step_x = -1;
		dda->side_x = (px - mx) * dda->delta_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_x = (mx + 1.0 - px) * dda->delta_x;
	}
}

void	init_dda_axis_y(t_data *data, t_dda *dda, double py, int my)
{
	dda->delta_y = calc_delta(data->ray.dir_y);
	if (data->ray.dir_y < 0)
	{
		dda->step_y = -1;
		dda->side_y = (py - my) * dda->delta_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_y = (my + 1.0 - py) * dda->delta_y;
	}
}

bool	process_dda_cell(t_data *data, t_dda *dda)
{
	char cell;

	cell = data->map.grid[dda->map_y][dda->map_x];
	if (cell == '1')
		return (true);
	if (cell == 'D')
	{
		data->ray.door_progress = lookup_door_progress(
			data, dda->map_x, dda->map_y);
		if (data->ray.door_progress <= 1)
		{
			data->ray.is_door = true;
			return (true);
		}
	}
	return (false);
}
