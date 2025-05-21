/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:24:42 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/09 17:08:05 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_dda(t_data *data, double angle, t_dda *dda)
{
	double 	px;
	double	py;
	int		mx;
	int		my;

	px = data->player.x;
	py = data->player.y;
	mx = (int)px;
	my = (int)py;
	data->ray.dir_x = cos(angle);
	data->ray.dir_y = sin(angle);

	init_dda_axis_x(data, dda, px, mx);
	init_dda_axis_y(data, dda, py, my);
	dda->map_x = mx;
	dda->map_y = my;
	data->ray.is_door = false;
	data->ray.door_progress = 0;
}

static void	perform_dda(t_data *data, t_dda *dda)
{
	while (1)
	{
		if (dda->side_x < dda->side_y)
		{
			dda->side_x += dda->delta_x;
			dda->map_x += dda->step_x;
			data->ray.side = 0;
		}
		else
		{
			dda->side_y += dda->delta_y;
			dda->map_y += dda->step_y;
			data->ray.side = 1;
		}
		if (process_dda_cell(data, dda))
			break;
	}
}

static void	compute_hit(t_data *data, double angle, t_dda *dda)
{
	double  dist;

	if (data->ray.side == 0)
	{
		dist = (dda->map_x - data->player.x +
			   (1 - dda->step_x) / 2) / data->ray.dir_x;
		data->ray.hit_y = data->player.y + dist * data->ray.dir_y;
		data->ray.wall_x = data->ray.hit_y - 
						  floor(data->ray.hit_y);
	}
	else
	{
		dist = (dda->map_y - data->player.y +
			   (1 - dda->step_y) / 2) / data->ray.dir_y;
		data->ray.hit_x = data->player.x + dist * data->ray.dir_x;
		data->ray.wall_x = data->ray.hit_x - 
						  floor(data->ray.hit_x);
	}
	data->ray.distance = dist * cos(angle - data->player.angle);
}

void	calculate_ray_data(t_data *data, double ray_angle)
{
	t_dda   dda;

	init_dda(data, ray_angle, &dda);
	perform_dda(data, &dda);
	compute_hit(data, ray_angle, &dda);
	data->ray.texture = get_wall_texture(data);
}