/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:37:41 by djelacik          #+#    #+#             */
/*   Updated: 2025/01/04 17:29:59 by djelacik         ###   ########.fr       */
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
			if (data->map.grid[y][x] == '1') // Seinät
				draw_square(data->image, screen_x, screen_y, TILE_SIZE * MINIMAP_SCALE, 0x000000);
			else // Lattia
				draw_square(data->image, screen_x, screen_y, TILE_SIZE * MINIMAP_SCALE, 0xAAAAAA);
			x++;
		}
		y++;
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
	size = 5; // Pelaajan koko minimapilla
	i = -size / 2;
	while (i <= size / 2)
	{
		j = -size / 2;
		while (j <= size / 2)
		{
			if (x + i >= 0 && x + i < data->width &&
				y + j >= 0 && y + j < data->height)
				mlx_put_pixel(data->image, x + i, y + j, 0xFF0000); // Punainen
			j++;
		}
		i++;
	}
}

double	normalize_angle(double angle)
{
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	while (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

//limit angle to 0 - 2 * M_PI
void	draw_mini_rays(t_data *data)
{
	double	ray_x;
	double	ray_y;
	double	angle;
	int		screen_x;
	int		screen_y;
	double	max_angle;

	//data->player.angle = normalize_angle(data->player.angle);
	//printf("player.angle: %f\n", data->player.angle);
	//angle = normalize_angle(data->player.angle - FOV / 2);
	angle = data->player.angle - FOV / 2;
	//max_angle = normalize_angle(data->player.angle + FOV / 2);
	max_angle = data->player.angle + FOV / 2;
	//assert(data->player.angle >= 0 && data->player.angle < 2 * M_PI);
	while (angle <= max_angle)
	{
		//assert(angle >= 0 && angle < 2 * M_PI);
		ray_x = data->player.x;
		ray_y = data->player.y;
		while (data->map.grid[(int)ray_y][(int)ray_x] != '1')
		{
			//assert(ray_x >= 0 && ray_x < data->map.width);
			//assert(ray_y >= 0 && ray_y < data->map.height);
			ray_x += cos(angle) * STEP_SIZE;
			ray_y += sin(angle) * STEP_SIZE;
			screen_x = ray_x * TILE_SIZE * MINIMAP_SCALE;
			screen_y = ray_y * TILE_SIZE * MINIMAP_SCALE;
			if (screen_x >= 0 && screen_x < data->width
				&& screen_y >= 0 && screen_y < data->height)
				mlx_put_pixel(data->image, screen_x, screen_y, GRAY_COLOR);
		}
		angle += 0.01;
		//angle = normalize_angle(angle);
	}
}

void	draw_square(mlx_image_t *image, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			// Piirrä ilman reunoja
			mlx_put_pixel(image, x + i, y + j, color);
			j++;
		}
		i++;
	}
}
