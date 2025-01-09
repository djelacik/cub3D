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

// static void	draw_wall_column(mlx_image_t *image, int x, int start_y, int end_y, int color)
// {
// 	int	y;

// 	y = start_y;
// 	while (y <= end_y)
// 	{
// 		if (y >= 0 && y < WIN_HEIGHT)
// 			mlx_put_pixel(image, x, y, color);
// 		y++;
// 	}
// }

static void	calculate_wall_limits(int *start_y, int *end_y, double corrected_distance)
{
	int wall_height;

	//wall_height = (TILE_SIZE / corrected_distance) * 7;
	wall_height = (int)(WIN_HEIGHT / corrected_distance);
	*start_y = (WIN_HEIGHT / 2) - (wall_height / 2);
	*end_y = (WIN_HEIGHT / 2) + (wall_height / 2);

	if (*start_y < 0)
		*start_y = 0;
	if (*end_y >= WIN_HEIGHT)
		*end_y = WIN_HEIGHT - 1;

	DBG_PRINT("Wall Height: %d, Start Y: %d, End Y: %d, Height Difference: %d\n", wall_height, *start_y, *end_y, *end_y - *start_y);
	DBG_PRINT("Wall Height: %d, Start Y: %d, End Y: %d\n", wall_height, *start_y, *end_y);
    DBG_PRINT("Height Change: %d\n", *end_y - *start_y); // Tämä tulostus
}

double	calculate_corrected_distance(double distance, double ray_angle, double player_angle)
{
	double corrected_distance;

	corrected_distance = distance * cos(ray_angle - player_angle);

	//if (corrected_distance < 10)
	//corrected_distance = 10;

	//corrected_distance = fmax(corrected_distance, 0.5);

	// Debug-tuloste
	DBG_PRINT("Distance: %f, Ray Angle: %f, Player Angle: %f, Corrected Distance: %f\n", 
		distance, ray_angle, player_angle, corrected_distance);

	return (corrected_distance);
}

void	draw_single_ray(t_data *data, double angle, int screen_x)
{
	t_ray	ray;
	int		start_y;
	int		end_y;
	double	corrected_distance;

	ray = calculate_ray(data, angle);
	corrected_distance = calculate_corrected_distance(ray.distance, angle, data->player.angle);

	calculate_wall_limits(&start_y, &end_y, corrected_distance);

	DBG_PRINT("Screen X: %d, Corrected Distance: %f, Start Y: %d, End Y: %d\n", screen_x, corrected_distance, start_y, end_y);

	//draw_wall_column(data->image, screen_x, start_y, end_y, simple_shading(0xFFB6C1, corrected_distance));
	draw_wall_texture(data, &ray, screen_x, start_y, end_y);
	//draw_wall_pattern_texture(data, &ray, screen_x, start_y, end_y);
}

void	draw_rays(t_data *data)
{
	double	angle;
	int		screen_x;

	// Alustetaan ensimmäisen säteen kulma
	angle = data->player.angle - FOV / 2;
	screen_x = 0;

	// Käy läpi kaikki näytön x-koordinaatit
	while (screen_x < WIN_WIDTH)
	{
		DBG_PRINT("Ray Angle: %f, Screen X: %d\n", angle, screen_x);
		// Käytä draw_single_ray-funktiota yhden säteen laskemiseen ja piirtämiseen
		draw_single_ray(data, angle, screen_x);

		// Siirry seuraavaan säteeseen
		angle += FOV / (WIN_WIDTH);
		screen_x++;
	}
}
