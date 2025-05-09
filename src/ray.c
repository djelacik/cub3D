/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:24:42 by aapadill          #+#    #+#             */
/*   Updated: 2025/02/21 18:00:30 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//TODO
void	calculate_ray_data(t_data *data, double ray_angle)
{
	double delta_dist_x;
	double delta_dist_y;
	double side_dist_x;
	double side_dist_y;
	int map_x;
	int map_y;
	int step_x;
	int step_y;

	data->ray.dir_x = cos(ray_angle);
	data->ray.dir_y = sin(ray_angle);

	map_x = (int)data->player.x;
	map_y = (int)data->player.y;

	if (data->ray.dir_x == 0)
		delta_dist_x = 1e30; //to avoid division by zero
	else
		delta_dist_x = fabs(1 /data->ray.dir_x);
	if (data->ray.dir_y == 0)
		delta_dist_y = 1e30; //to avoid division by zero
	else
		delta_dist_y = fabs(1 / data->ray.dir_y);

	if (data->ray.dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (data->player.x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - data->player.x) * delta_dist_x;
	}
	if (data->ray.dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (data->player.y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - data->player.y) * delta_dist_y;
	}
	data->ray.is_door = false;
	data->ray.door_progress = 0;
	// DDA: Eteneminen gridissä
	while (1)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			data->ray.side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			data->ray.side = 1;
		}
		char cell = data->map.grid[map_y][map_x];
		if (cell == '1') //stop ray, this is a wall
			break;
		else if (cell == 'D') //this is a door
		{
			data->ray.door_progress = lookup_door_progress(data, map_x, map_y);
			if (data->ray.door_progress <= 1)
			{
				data->ray.is_door = true;
				break;
			}
		}
	}
	if (data->ray.side == 0)
	{
		//data->ray.hit_x = map_x;
		data->ray.distance = (map_x - data->player.x + (1 - step_x) / 2) / data->ray.dir_x;
		data->ray.hit_y = data->player.y + data->ray.distance * data->ray.dir_y;
		data->ray.wall_x = data->ray.hit_y - floor(data->ray.hit_y);
	}
	else
	{
		//data->ray.hit_y = map_y;
		data->ray.distance = (map_y - data->player.y + (1 - step_y) / 2) / data->ray.dir_y;
		data->ray.hit_x = data->player.x + data->ray.distance * data->ray.dir_x;
		data->ray.wall_x = data->ray.hit_x - floor(data->ray.hit_x);
	}
	data->ray.distance = data->ray.distance * cos(ray_angle - data->player.angle); //correct distance?
	data->ray.texture = get_wall_texture(data);
}
