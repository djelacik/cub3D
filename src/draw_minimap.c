/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:37:41 by djelacik          #+#    #+#             */
/*   Updated: 2025/05/21 15:00:12 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_mini_map(t_data *data)
{
	int	x;
	int	y;
	int	screen_x;
	int	screen_y;

	y = 0;
	while (data->map.grid[y])
	{
		x = 0;
		while (data->map.grid[y][x])
		{
			screen_x = x * TILE_SIZE * MINIMAP_SCALE;
			screen_y = y * TILE_SIZE * MINIMAP_SCALE;
			if (data->map.grid[y][x] == '1')
				data->aux_color = BLUE_COLOR;
			else if (data->map.grid[y][x] == 'D' && is_wall(data,
						(double)x, (double)y))
				data->aux_color = GREEN_COLOR;
			else
				data->aux_color = BLUE_COLOR_2;
			draw_square(data, screen_x, screen_y, TILE_SIZE * MINIMAP_SCALE);
			x++;
		}
		y++;
	}
}

void	draw_square(t_data *data, int x, int y, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(data->image, x + i, y + j, data->aux_color);
			j++;
		}
		i++;
	}
}

void	draw_mini_player(t_data *data)
{
	int	x;
	int	y;
	int	size;
	int	i;
	int	j;

	x = (int)(data->player.x * TILE_SIZE * MINIMAP_SCALE);
	y = (int)(data->player.y * TILE_SIZE * MINIMAP_SCALE);
	size = 5;
	i = -size / 2;
	while (i <= size / 2)
	{
		j = -size / 2;
		while (j <= size / 2)
		{
			if (x + i >= 0 && x + i < data->width
				&& y + j >= 0 && y + j < data->height)
				mlx_put_pixel(data->image, x + i, y + j, RED_COLOR);
			j++;
		}
		i++;
	}
}

//TODO: reduce one variable
//limit angle to 0 - 2 * M_PI
//rays look more like waves wtf
//make this dynamic (portion of the map depending on player's position)
void	draw_mini_rays(t_data *data)
{
	double	ray_x;
	double	ray_y;
	double	angle;
	double	screen_x;
	double	screen_y;
	double	max_angle;

	angle = data->player.angle - FOV / 2;
	max_angle = data->player.angle + FOV / 2;
	while (angle <= max_angle)
	{
		ray_x = data->player.x;
		ray_y = data->player.y;
		while (!is_wall(data, ray_x, ray_y))
		{
			ray_x += cos(angle) * STEP_SIZE;
			ray_y += sin(angle) * STEP_SIZE;
			screen_x = ray_x * TILE_SIZE * MINIMAP_SCALE;
			screen_y = ray_y * TILE_SIZE * MINIMAP_SCALE;
			if (screen_x >= 0 && screen_x < data->width
				&& screen_y >= 0 && screen_y < data->height)
				mlx_put_pixel(data->image, (int)screen_x, (int)screen_y, YELLOW_COLOR);
		}
		angle += 0.01;
	}
}
