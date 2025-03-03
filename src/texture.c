/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:02:57 by aapadill          #+#    #+#             */
/*   Updated: 2025/02/21 18:01:01 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

uint32_t	get_texture_color(mlx_texture_t *texture, int x, int y)
{
	return (*(uint32_t *)(texture->pixels + y * texture->width * 4 + x * 4));
}

mlx_texture_t *get_wall_texture(t_data *data, double dir_x, double dir_y, int side)
{
	if (side == 0) // X-seinä
	{
		if (dir_x > 0) // Itään
			return data->textures->east;
		else // Länteen
			return data->textures->west;
	}
	else // Y-seinä
	{
		if (dir_y > 0) // Etelään
			return data->textures->south;
		else // Pohjoiseen
			return data->textures->north;
	}
}

void	draw_wall_texture(t_data *data, t_ray *ray, int screen_x, int start_y, int end_y)
{
	int		y;
	uint32_t	tex_x;
	uint32_t	tex_y;
	uint32_t	color;
	uint32_t	shaded_color;

	tex_x = ray->wall_x * ray->texture->width;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= ray->texture->width)
		tex_x = ray->texture->width - 1;
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
		tex_x = ray->texture->width - tex_x - 1;

	y = start_y;
	while (y <= end_y)
	{
		tex_y = ((y - start_y) / (double)(end_y - start_y)) * ray->texture->height;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= ray->texture->height)
			tex_y = ray->texture->height - 1;
		color = get_texture_color(ray->texture, tex_x, tex_y);
		shaded_color = simple_shading(color, ray->distance);
		mlx_put_pixel(data->image, screen_x, y, shaded_color);
		y++;
	}
}

void draw_wall_pattern_texture(t_data *data, t_ray *ray, int screen_x, int start_y, int end_y, double scale)
{
	if (ray->texture == NULL || ray->texture->width == 0 || ray->texture->height == 0)
		return; // Invalid texture

	int tex_x;
	int y;
	uint32_t color;
	uint32_t shaded_color;
	int wall_height = end_y - start_y + 1;
	int tex_width = ray->texture->width;
	int tex_height = ray->texture->height;
	double step_y;
	double tex_pos_y;

	// Handle scaling: if scale <= 0, fit as many textures as possible
	if (scale <= 0.0)
	{
		// Fit as many textures as the wall height allows
		scale = (double)wall_height / (double)tex_height;
		if (scale < 1.0)
			scale = 1.0; // Ensure at least one repeat
	}

	// Calculate the step increment for texture Y coordinate based on the scale
	// A higher scale means the texture repeats more times (smaller texture size)
	step_y = ((double)tex_height * scale) / (double)wall_height;
	tex_pos_y = 0.0;

	// Calculate the scaled and wrapped X coordinate on the texture
	double scaled_wall_x = ray->wall_x * scale;
	double wrapped_wall_x = scaled_wall_x - floor(scaled_wall_x); // Equivalent to fmod(scaled_wall_x, 1.0)
	tex_x = (int)(wrapped_wall_x * tex_width);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
		tex_x = tex_width - tex_x - 1;

	// Iterate over each Y position on the screen
	y = start_y;
	while (y <= end_y)
	{
		// Calculate the Y coordinate on the texture with wrapping
		int current_tex_y = ((int)tex_pos_y) % tex_height;
		if (current_tex_y < 0)
			current_tex_y += tex_height; // Ensure positive index

		// Get the color from the texture
		color = get_texture_color(ray->texture, tex_x, current_tex_y);

		// Apply shading based on distance
		shaded_color = simple_shading(color, ray->distance);

		// Draw the pixel on the screen
		mlx_put_pixel(data->image, screen_x, y, shaded_color);

		// Increment the texture position
		tex_pos_y += step_y;
		y++;
	}
}
