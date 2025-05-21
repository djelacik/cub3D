/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:29:26 by djelacik          #+#    #+#             */
/*   Updated: 2025/05/21 15:03:48 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_walls(t_data *data)
{
	double	dist_to_plane;
	double	screen_x;
	double	offset;
	double	angle_offset;
	double	ray_angle;

	dist_to_plane = ((double)data->width / 2.0) / tan(FOV / 2.0);
	screen_x = 0;
	while ((int)screen_x < data->width)
	{
		offset = (screen_x + 0.5) - (double)((double)data->width / 2.0);
		angle_offset = atan(offset / dist_to_plane);
		ray_angle = data->player.angle + angle_offset;
		draw_wall_column(data, ray_angle, (int)screen_x);
		screen_x++;
	}
}

/*
	Calculates ray properties
	Computes full (virtual wall height) and its stating/ending positions
	Clips the drawing area to the visible screen (but keeps the original 
	positions for texture mapping)
	Passes both the visible drawing range and the original wall info
*/
void	draw_wall_column(t_data *data, double ray_angle, int screen_x)
{
	int		center_y;

	calculate_ray_data(data, ray_angle);
	data->column.wall_height = (int)(data->height / data->ray.distance);
	center_y = (int)(data->height / 2 + data->camera.shake_offset);
	data->column.orig_start_y = center_y - (data->column.wall_height / 2);
	data->column.orig_end_y = center_y + (data->column.wall_height / 2);
	data->column.vis_start_y = data->column.orig_start_y;
	data->column.vis_end_y = data->column.orig_end_y;
	if (data->column.vis_start_y < 0)
		data->column.vis_start_y = 0;
	if (data->column.vis_end_y >= data->height)
		data->column.vis_end_y = data->height - 1;
	draw_wall_texture(data, screen_x);
}
