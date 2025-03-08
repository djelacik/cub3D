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

double	calculate_distance(t_data *data, double angle, t_ray *ray)
{
	double	ray_x;
	double	ray_y;
	double	distance;

	ray_x = data->player.x;
	ray_y = data->player.y;
	while (!is_wall(data, ray_x, ray_y))
	{
		ray_x += cos(angle) * STEP_SIZE;
		ray_y += sin(angle) * STEP_SIZE;
	}
	ray->hit_x = ray_x;
	ray->hit_y = ray_y;
	distance = sqrt(pow(ray_x - data->player.x, 2) + pow(ray_y - data->player.y, 2));
	return (distance);
}

int calculate_hit_side(t_data *data, double angle, t_ray *ray)
{
	double ray_dir_x;
	double ray_dir_y;
	double delta_dist_x;
	double delta_dist_y;
	double side_dist_x;
	double side_dist_y;
	int map_x;
	int map_y;
	int step_x;
	int step_y;
	int hit_side;

	ray_dir_x = cos(angle);
	ray_dir_y = sin(angle);

	map_x = (int)data->player.x;
	map_y = (int)data->player.y;

	delta_dist_x = fabs(1 / ray_dir_x);
	delta_dist_y = fabs(1 / ray_dir_y);

	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (data->player.x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - data->player.x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (data->player.y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - data->player.y) * delta_dist_y;
	}
	ray->is_door = false;
	ray->door_progress = 0;
	// DDA: Eteneminen gridissä
	while (1)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			hit_side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			hit_side = 1;
		}
		char cell = data->map.grid[map_y][map_x];
		if (cell == '1') //stop ray, this is a wall
			break;
		else if (cell == 'D') //this is a door
		{
			double progress = lookup_door_progress(data, map_x, map_y);
			if (progress < 0.8)
			{
				ray->is_door = true;
				ray->door_progress = progress;
				break;
			}
		}
	}
	return hit_side;
}

double	get_wall_x(t_ray *ray)
{
	if (ray->side == 0)
		return (ray->hit_y - floor(ray->hit_y));
	else
		return (ray->hit_x - floor(ray->hit_x));
}

bool	calculate_ray(t_data *data, double angle, t_ray *ray)
{
	ray->distance = calculate_distance(data, angle, ray);
	ray->side = calculate_hit_side(data, angle, ray);
	ray->wall_x = get_wall_x(ray);
	if (ray->is_door)
	{
		if (ray->door_progress > 0.8)
			ray->texture = get_wall_texture(data, cos(angle), sin(angle), ray->side);
		else
			ray->texture = data->textures->door;
	}
	else
		ray->texture = get_wall_texture(data, cos(angle), sin(angle), ray->side);
	return (true);
}
