/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 21:02:57 by aapadill          #+#    #+#             */
/*   Updated: 2025/01/09 21:03:01 by aapadill         ###   ########.fr       */
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
	int		tex_x;
	int		tex_y;
	uint32_t	color;
	uint32_t	shaded_color;

	tex_x = (int)(ray->wall_x * ray->texture->width);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
		tex_x = ray->texture->width - tex_x - 1;

	//DBG_PRINT("Wall X: %f, Tex X: %d, Ray Side: %d\n", ray->wall_x, tex_x, ray->side);
	//DBG_PRINT("Drawing Wall: Screen X: %d, Tex X: %d, Start Y: %d, End Y: %d\n", screen_x, tex_x, start_y, end_y);

	y = start_y;
	while (y <= end_y)
	{
		tex_y = (int)(((y - start_y) / (double)(end_y - start_y)) * ray->texture->height);
		color = get_texture_color(ray->texture, tex_x, tex_y);
		shaded_color = simple_shading(color, ray->distance);
		mlx_put_pixel(data->image, screen_x, y, shaded_color);
		y++;
	}
}

void draw_wall_pattern_texture(t_data *data, t_ray *ray, int screen_x, int start_y, int end_y)
{
	int	tex_x;
	int	y;

    tex_x = (int)(ray->wall_x * ray->texture->width);

    if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
        tex_x = ray->texture->width - tex_x - 1;

	y = start_y;
    //from the top of the wall (start_y) to the bottom (end_y)
    while (y <= end_y)
    {
        //repeat every 'texture->height' pixels on the screen.
        int wrappedTexY = (y - start_y) % (int)ray->texture->height;

        //if wrappedTexY is negative, push it back into [0..texture->height-1].
        if (wrappedTexY < 0)
            wrappedTexY += ray->texture->height;

        uint32_t color = get_texture_color(ray->texture, tex_x, wrappedTexY);

        if (y >= 0 && y < WIN_HEIGHT)
            mlx_put_pixel(data->image, screen_x, y, color);

		y++;
    }
}
