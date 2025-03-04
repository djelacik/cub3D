/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:29:26 by djelacik          #+#    #+#             */
/*   Updated: 2025/01/05 22:34:48 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	calculate_wall_limits(t_data *data, int *start_y, int *end_y, double corrected_distance)
{
	int wall_height;

	wall_height = (int)(data->height / corrected_distance);
	*start_y = (data->height / 2) - (wall_height / 2);
	*end_y = (data->height / 2) + (wall_height / 2);

	if (*start_y < 0)
		*start_y = 0;
	if (*end_y >= data->height)
		*end_y = data->height - 1;
}

double	calculate_corrected_distance(double distance, double ray_angle, double player_angle)
{
	return (distance * cos(ray_angle - player_angle));
}

void	draw_single_ray(t_data *data, double angle, int screen_x)
{
	t_ray	ray;
	int		start_y;
	int		end_y;
	double	corrected_distance;

	ft_memset(&ray, 0, sizeof(t_ray));
	calculate_ray(data, angle, &ray);
	corrected_distance = calculate_corrected_distance(ray.distance, angle, data->player.angle);

	calculate_wall_limits(data, &start_y, &end_y, corrected_distance);
	//draw_wall_column(data->image, screen_x, start_y, end_y, simple_shading(0xFFB6C1, corrected_distance));
	draw_wall_texture(data, &ray, screen_x, start_y, end_y);
}

/*
void	draw_rays(t_data *data)
{
	double	angle;
	int		screen_x;

	angle = data->player.angle - FOV / 2;
	screen_x = 0;

	while (screen_x < data->width)
	{
		draw_single_ray(data, angle, screen_x);

		angle += FOV / (data->width); //-1?
		screen_x++;
	}
}*/

void	draw_rays(t_data *data)
{
	double	distToPlane;
	int		screen_x;
	double	offset;
	double	angle_offset;
	double	ray_angle;

	distToPlane = ((double)data->width / 2) / tan(FOV / 2);
	screen_x = 0;
	while (screen_x < data->width)
	{
		offset = (screen_x + 0.5) - ((double)data->width / 2.0);
		angle_offset = atan(offset / distToPlane);
		ray_angle = data->player.angle + angle_offset;
		//data->player.angle = data->player.angle + angle_offset;
		draw_single_ray(data, ray_angle, screen_x);
		screen_x++;
	}
}
