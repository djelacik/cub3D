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

bool	load_texture(char *path, mlx_texture_t **texture)
{
	*texture = mlx_load_png(path);
	if (!*texture)
		return (false);
	return (true);
}

bool	textures_ready(t_data *data)
{
	t_textures	*t;

	t = data->textures;
	return (t->north && t->south && t->west && t->east);
}

bool	load_hud_textures(t_data *data)
{
	bool	ok[5];

	ft_memset(ok, 0, sizeof(bool) * 5);
	data->hud_hands = gc_alloc(sizeof(mlx_texture_t *) * 5);
	if (!data->hud_hands)
		return (false);
	ok[0] = load_texture("textures/hand/hand111.png", &data->hud_hands[0]);
	ok[1] = load_texture("textures/hand/hand222.png", &data->hud_hands[1]);
	ok[2] = load_texture("textures/hand/hand333.png", &data->hud_hands[2]);
	ok[3] = load_texture("textures/hand/hand444.png", &data->hud_hands[3]);
	ok[4] = load_texture("textures/hand/hand555.png", &data->hud_hands[4]);
	data->hud_frame_count = 5;
	if (!ok[0] || !ok[1] || !ok[2] || !ok[3] || !ok[4])
	{
		data->error_msg = "Failed to load HUD textures";
		free_hud_textures(data);
		return (false);
	}
	return (true);
}

//check int x and int y type
uint32_t	get_texture_color(mlx_texture_t *texture, int x, int y)
{
	if (x < 0 || x >= (int)texture->width || y < 0 || y >= (int)texture->height)
		return (0);
	return (*(uint32_t *)(texture->pixels + y * texture->width * 4 + x * 4));
}

mlx_texture_t *get_wall_texture(t_data *data)
{
	if (data->ray.is_door)
		return data->textures->door;
	if (data->ray.side == 0)
	{
		if (data->ray.dir_x > 0)
			return data->textures->east;
		else
			return data->textures->west;
	}
	else
	{
		if (data->ray.dir_y > 0)
			return data->textures->south;
		else
			return data->textures->north;
	}
}
