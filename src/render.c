/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:21:34 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/21 15:10:22 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render(t_data *data)
{
	mlx_resize_hook(data->mlx, &my_resize_callback, (void *)data);
	if (data->resize_pending)
	{
		data->width = data->new_width;
		data->height = data->new_height;
		mlx_delete_image(data->mlx, data->image);
		data->image = mlx_new_image(data->mlx, data->new_width,
				data->new_height);
		mlx_image_to_window(data->mlx, data->image, 0, 0);
		data->player.speed = (double)data->height * PLAYER_SPEED;
		data->camera.x = data->width / 2;
		data->camera.y = data->height / 2;
		printf("Render will now happen with %dx%d\n", data->width,
			data->height);
		data->resize_pending = false;
	}
	draw_floor_and_ceiling(data);
	draw_walls(data);
	draw_mini_map(data);
	draw_mini_player(data);
	draw_mini_rays(data);
	draw_hud_hands(data);
	shooting_animation(data);
}
