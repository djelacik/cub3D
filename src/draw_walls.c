/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:29:26 by djelacik          #+#    #+#             */
/*   Updated: 2025/05/08 14:53:52 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_walls(t_data *data)
{
	double	distToPlane;
	double	screen_x; //mmmmmm
	double	offset;
	double	angle_offset;
	double	ray_angle;

	distToPlane = ((double)data->width / 2.0) / tan(FOV / 2.0);
	screen_x = 0;
	while ((int)screen_x < data->width)
	{
		offset = (screen_x + 0.5) - (double)((double)data->width / 2.0);
		angle_offset = atan(offset / distToPlane);
		ray_angle = data->player.angle + angle_offset;
		draw_wall_column(data, ray_angle, (int)screen_x);
		screen_x++;
	}
}

void	draw_wall_column(t_data *data, double ray_angle, int screen_x)
{
	t_ray	ray;
	int		orig_start_y;
	int		orig_end_y;
	int		vis_start_y;
	int		vis_end_y;
	int		wall_height;
	int		center_y;

	// Calculate ray properties
	calculate_ray_data(data, ray_angle, &ray);

	// Compute the full (virtual) wall height and its starting/ending positions
	wall_height = (int)(data->height / ray.distance);
	center_y = (int)(data->height / 2 + data->camera.shake_offset);
	orig_start_y = center_y - (wall_height / 2);
	orig_end_y = center_y + (wall_height / 2);

	// Clip the drawing area to the visible screen (but keep the original positions for texture mapping)
	vis_start_y = orig_start_y;
	vis_end_y = orig_end_y;
	if (vis_start_y < 0)
		vis_start_y = 0;
	if (vis_end_y >= data->height)
		vis_end_y = data->height - 1;

	// Pass both the visible drawing range and the original wall info
	draw_wall_texture(data, &ray, screen_x, vis_start_y, vis_end_y, orig_start_y, wall_height);
}

void	draw_wall_texture(t_data *data, t_ray *ray, int screen_x, int vis_start_y, int vis_end_y, int orig_start_y, int wall_height)
{
	int			y;
	int			tex_x;
	int			tex_y;
	uint32_t	color;
	uint32_t	shaded_color;

	tex_x = ray->wall_x * ray->texture->width;
	if (tex_x >= (int)ray->texture->width)
		tex_x = ray->texture->width - 1;
	if (ray->is_door)
	{
		int offset = (int)(ray->door_progress * ray->texture->width);
		tex_x = (tex_x + offset) % ray->texture->width;
		if (tex_x < offset)
		{
			ray->is_door = false;
			ray->texture = get_wall_texture(data, ray);
			ray->is_door = true; // Necessary?
		}
	}
	y = vis_start_y;
	while (y <= vis_end_y)
	{
		// Compute the texture y-coordinate using the original (unclipped) wall parameters
		tex_y = ((y - orig_start_y) * ray->texture->height) / wall_height;
		if (tex_y >= (int)ray->texture->height)
			tex_y = ray->texture->height - 1;
		color = get_texture_color(ray->texture, tex_x, tex_y);
		shaded_color = simple_shading(color, ray->distance);
		mlx_put_pixel(data->image, screen_x, y, shaded_color);
		y++;
	}
}
