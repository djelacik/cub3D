/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:24:42 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/09 21:24:43 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	calculate_distance(t_player player, double angle, char **map, t_ray *ray)
{
	double	ray_x;
	double	ray_y;
	double	distance;

	ray_x = player.x;
	ray_y = player.y;
	while (!is_wall(map, ray_x, ray_y))
	{
		ray_x += cos(angle) * STEP_SIZE;
		ray_y += sin(angle) * STEP_SIZE;
	}
	ray->hit_x = ray_x;
	ray->hit_y = ray_y;
	distance = sqrt(pow(ray_x - player.x, 2) + pow(ray_y - player.y, 2));
	return (distance);
}

int calculate_hit_side(t_player player, double angle, char **map)
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

    map_x = (int)player.x;
    map_y = (int)player.y;

    delta_dist_x = fabs(1 / ray_dir_x);
    delta_dist_y = fabs(1 / ray_dir_y);

    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (player.x - map_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - player.x) * delta_dist_x;
    }
    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (player.y - map_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - player.y) * delta_dist_y;
    }

    // DDA: Eteneminen gridissä
    while (1)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            hit_side = 0; // Osuma x-seinään
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            hit_side = 1; // Osuma y-seinään
        }
        if (map[map_y][map_x] == '1') // Osuma seinään
            break;
    }

    return hit_side;
}

double	get_wall_x(double hit_x, double hit_y, int hit_side)
{
	if (hit_side == 0)
		return (hit_y - floor(hit_y));
	else
		return (hit_x - floor(hit_x));
}

t_ray	calculate_ray(t_data *data, double angle)
{
	t_ray ray;

	ray.distance = calculate_distance(data->player, angle, data->map, &ray);
	ray.side = calculate_hit_side(data->player, angle, data->map);
	ray.wall_x = get_wall_x(ray.hit_x, ray.hit_y, ray.side);
	ray.texture = get_wall_texture(data, cos(angle), sin(angle), ray.side);

	return (ray);
}