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
