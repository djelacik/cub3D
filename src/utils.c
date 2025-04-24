/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:34:31 by djelacik          #+#    #+#             */
/*   Updated: 2025/03/04 14:44:23 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	lookup_door_progress(t_data *data, int x, int y)
{
	int i = 0;
	while (i < data->door_count)
	{
		if (data->doors[i].x == x && data->doors[i].y == y)
			return data->doors[i].progress;
		i++;
	}
	return 0;
}

//make smoother, currently it's buggy if moving in a distance == 2
void update_doors(t_data *data)
{
	int	i = 0;
	while (i < data->door_count)
	{
		t_door *door = &data->doors[i];
		double dx = door->x + 0.5 - data->player.x;
		double dy = door->y + 0.5 - data->player.y;
		double distance = sqrt(dx * dx + dy * dy);

		// If player is close enough and roughly facing the door, trigger it
		if (distance < 3) /* adjust threshold */
		{
			// Check the angle between player direction and the door
			// (For simplicity, you might compare the player's angle with the angle to the door)
			// If conditions are met, start opening:
			if (door->state == CLOSED)
			{
				door->state = OPENING;
			}
		}
		
		// Animate door opening/closing
		if (door->state == OPENING)
		{
			door->progress += DOOR_OPENING_SPEED; // adjust speed as needed
			if (door->progress > 1.0)
			{
				door->progress = 1.01;
				door->state = OPEN;
			}
		}
		else if (door->state == OPEN)
		{
			// Optionally, if the player moves away, start closing the door
			if (distance > 3)
				door->state = CLOSING;
		}
		else if (door->state == CLOSING)
		{
			door->progress -= DOOR_OPENING_SPEED;
			if (door->progress <= 0.0)
			{
				door->progress = 0.0;
				door->state = CLOSED;
			}
		}
		i++;
	}
}

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

bool	is_wall(t_data *data, double x, double y)
{
	char	cell;

	cell = get_map_cell(data, x, y);
	if (cell == '1')
		return (1);
	else if (cell == 'D')
	{
		int i = 0;
		while (i < data->door_count)
		{
			if (data->doors[i].x == (int)x && data->doors[i].y == (int)y)
			{
				// If door is closed or only partially open, consider it a wall
				if (data->doors[i].state == CLOSED || data->doors[i].progress < 0.8)
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

void	draw_floor_and_ceiling(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (y < data->height / 2)
				mlx_put_pixel(data->image, x, y, data->ceiling); // Katon väri
			else
				mlx_put_pixel(data->image, x, y, data->floor); // Lattian väri
			x++;
		}
		y++;
	}
}


// double	get_wall_x(t_ray *ray)
// {
// 	if (ray->side == 0)
// 		return (ray->hit_y - floor(ray->hit_y));
// 	else
// 		return (ray->hit_x - floor(ray->hit_x));
// }

// bool	calculate_ray(t_data *data, double angle, t_ray *ray)
// {
// 	//ft_memset(ray, 0, sizeof(t_ray));
// 	//ray->distance = calculate_distance(data, angle, ray);
// 	ray->side = calculate_hit_side(data, angle, ray);
// 	ray->wall_x = get_wall_x(ray);
// 	//assert(ray->wall_x >= 0 && ray->wall_x <= 1);
	
// 	return (true);
// }

// double	calculate_distance(t_data *data, double angle, t_ray *ray)
// {
// 	double	ray_x;
// 	double	ray_y;
// 	double	distance;

	
// 	ray_x = data->player.x;
// 	ray_y = data->player.y;
// 	while (!is_wall(data, ray_x, ray_y))
// 	{
// 		ray_x += cos(angle);//* STEP_SIZE;
// 		ray_y += sin(angle);//* STEP_SIZE;
// 	}
// 	ray->hit_x = ray_x;
// 	ray->hit_y = ray_y;
// 	distance = sqrt(pow(ray_x - data->player.x, 2) + pow(ray_y - data->player.y, 2));
// 	//return (distance * cos(angle - data->player.angle));
// 	return (distance);
// }


// double	calculate_corrected_distance(double distance, double ray_angle, double player_angle)
// {
// 	return (distance * cos(ray_angle - player_angle));
// }

// static void	draw_wall_column(t_data *data, int x, int start_y, int end_y, int color)
// {
// 	int	y;

// 	y = start_y;
// 	while (y <= end_y)
// 	{
// 		if (y >= 0 && y < data->height)
// 			mlx_put_pixel(data->image, x, y, color);
// 		y++;
// 	}
// }


//check types
// static void	calculate_wall_limits(t_data *data, int *start_y, int *end_y, double ray_distance)
// {
// 	int wall_height;

// 	wall_height = (int)(data->height / ray_distance);
// 	//if (wall_height > data->height)
// 	//	wall_height = data->height;
// 	*start_y = (data->height / 2) - (wall_height / 2);
// 	*end_y = (data->height / 2) + (wall_height / 2);
// 	if (*start_y < 0)
// 		*start_y = 0;
// 	if (*end_y >= data->height)
// 		*end_y = data->height - 1;
// }

/*
void	draw_wall_texture(t_data *data, t_ray *ray, int screen_x, int start_y, int end_y)
{
	int			y;
	uint32_t	tex_x;
	uint32_t	tex_y;
	uint32_t	color;
	uint32_t	shaded_color;

	tex_x = ray->wall_x * ray->texture->width;
	if (tex_x >= ray->texture->width)
		tex_x = ray->texture->width - 1;
	if (ray->is_door && ray->texture == data->textures->door)
	{
		int offset = (int)(ray->door_progress * ray->texture->width);
		tex_x = (tex_x + offset) % ray->texture->width;
	}
	else if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
		tex_x = ray->texture->width - tex_x - 1;
	y = start_y;
	while (y <= end_y)
	{
		tex_y = (uint32_t)(((y - start_y) / (double)(end_y - start_y)) * ray->texture->height);
		if (tex_y >= ray->texture->height)
			tex_y = ray->texture->height - 1;
		color = get_texture_color(ray->texture, tex_x, tex_y);
		shaded_color = simple_shading(color, ray->distance);
		mlx_put_pixel(data->image, screen_x, y, shaded_color);
		y++;
	}
}
*/