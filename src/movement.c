/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 15:40:09 by djelacik          #+#    #+#             */
/*   Updated: 2025/01/04 18:55:00 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	handle_movement(t_data *data)
{
	double	new_x;
	double	new_y;

	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		new_x = data->player.x + cos(data->player.angle) * 0.01;
		new_y = data->player.y + sin(data->player.angle) * 0.01;
		if (!is_wall(data->map, new_x, data->player.y))
			data->player.x = new_x;
		if (!is_wall(data->map, data->player.x, new_y))
			data->player.y = new_y;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		new_x = data->player.x - cos(data->player.angle) * 0.01;
		new_y = data->player.y - sin(data->player.angle) * 0.01;
		if (!is_wall(data->map, new_x, data->player.y))
			data->player.x = new_x;
		if (!is_wall(data->map, data->player.x, new_y))
			data->player.y = new_y;
	}
}

static void	handle_strafe(t_data *data)
{
	double	new_x;
	double	new_y;

	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		new_x = data->player.x - sin(data->player.angle) * 0.01;
		new_y = data->player.y + cos(data->player.angle) * 0.01;
		if (!is_wall(data->map, new_x, data->player.y))
			data->player.x = new_x;
		if (!is_wall(data->map, data->player.x, new_y))
			data->player.y = new_y;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		new_x = data->player.x + sin(data->player.angle) * 0.01;
		new_y = data->player.y - cos(data->player.angle) * 0.01;
		if (!is_wall(data->map, new_x, data->player.y))
			data->player.x = new_x;
		if (!is_wall(data->map, data->player.x, new_y))
			data->player.y = new_y;
	}
}

static void	handle_rotation(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.angle -= 0.01;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.angle += 0.01;
}

static void	render(t_data *data)
{
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	draw_floor_and_ceiling(data);
	draw_mini_map(data);
	draw_mini_player(data);
	draw_mini_rays(data);
	draw_rays(data);
}

void	loop_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	handle_movement(data);
	handle_strafe(data);
	handle_rotation(data);
	render(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}
