/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 11:15:13 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/21 11:15:58 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	select_tex_x(t_ray *ray)
{
	int tex_x;
	
	tex_x = ray->wall_x * ray->texture->width;
	if (tex_x >= (int)ray->texture->width)
		tex_x = ray->texture->width - 1;
	return tex_x;
}

static int	select_tex_y(t_data *data, int y)
{
	int relative_y;
	int	tex_height;
	int	wall_height;
	int	tex_y;
	
	relative_y = y - data->column.orig_start_y;
	tex_height = data->ray.texture->height;
	wall_height = data->column.wall_height;

	tex_y = (relative_y * tex_height) / wall_height;
	if (tex_y >= tex_height)
		tex_y = tex_height - 1;
	return tex_y;
}

static int	adjust_tex_x_for_door(t_data *data, int tex_x)
{
	int offset;
	int adjusted;

	if (!data->ray.is_door)
		return tex_x;
	offset = (int)(data->ray.door_progress * data->ray.texture->width);
	adjusted = (tex_x + offset) % data->ray.texture->width;
	if (adjusted < offset)
	{
		data->ray.is_door = false;
		data->ray.texture = get_wall_texture(data);
		data->ray.is_door = true;
	}
	return adjusted;
}

//compute the texture y-coordinate using the original (unclipped) wall parameters
void	draw_wall_texture(t_data *data, int screen_x)
{
	int			y;
	int			tex_x;
	int			tex_y;
	uint32_t	color;

	tex_x = select_tex_x(&data->ray);
	tex_x = adjust_tex_x_for_door(data, tex_x);
	y = data->column.vis_start_y;
	while (y <= data->column.vis_end_y)
	{
		tex_y = select_tex_y(data, y);
		color = get_texture_color(data->ray.texture, tex_x, tex_y);
		mlx_put_pixel(data->image, screen_x, y, shading(color, data->ray.distance));
		y++;
	}
}
