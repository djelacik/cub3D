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

//check int x and int y type
uint32_t	get_texture_color(mlx_texture_t *texture, int x, int y)
{
	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
		return (0);
	return (*(uint32_t *)(texture->pixels + y * texture->width * 4 + x * 4));
}

mlx_texture_t *get_wall_texture(t_data *data, t_ray *ray)
{
	if (ray->is_door)
		return data->textures->door;
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return data->textures->east;
		else
			return data->textures->west;
	}
	else
	{
		if (ray->dir_y > 0)
			return data->textures->south;
		else
			return data->textures->north;
	}
}

