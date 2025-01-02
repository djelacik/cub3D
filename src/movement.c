/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 15:40:09 by djelacik          #+#    #+#             */
/*   Updated: 2025/01/02 13:47:56 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	handle_movement(t_data *data, mlx_key_data_t keydata)
{
	double	new_x;
	double	new_y;

	if (keydata.key == MLX_KEY_W)
	{
		new_x = data->player.x + cos(data->player.angle) * 0.1;
		new_y = data->player.y + sin(data->player.angle) * 0.1;
		if (!is_wall(data->map, new_x, data->player.y))
			data->player.x = new_x;
		if (!is_wall(data->map, data->player.x, new_y))
			data->player.y = new_y;
	}
	if (keydata.key == MLX_KEY_S)
	{
		new_x = data->player.x - cos(data->player.angle) * 0.1;
		new_y = data->player.y - sin(data->player.angle) * 0.1;
		if (!is_wall(data->map, new_x, data->player.y))
			data->player.x = new_x;
		if (!is_wall(data->map, data->player.x, new_y))
			data->player.y = new_y;
	}
}

static void	handle_strafe(t_data *data, mlx_key_data_t keydata)
{
	double	new_x;
	double	new_y;

	if (keydata.key == MLX_KEY_D)
	{
		new_x = data->player.x - sin(data->player.angle) * 0.1;
		new_y = data->player.y + cos(data->player.angle) * 0.1;
		if (!is_wall(data->map, new_x, data->player.y))
			data->player.x = new_x;
		if (!is_wall(data->map, data->player.x, new_y))
			data->player.y = new_y;
	}
	if (keydata.key == MLX_KEY_A)
	{
		new_x = data->player.x + sin(data->player.angle) * 0.1;
		new_y = data->player.y - cos(data->player.angle) * 0.1;
		if (!is_wall(data->map, new_x, data->player.y))
			data->player.x = new_x;
		if (!is_wall(data->map, data->player.x, new_y))
			data->player.y = new_y;
	}
}

static void	handle_rotation(t_data *data, mlx_key_data_t keydata)
{
	if (keydata.key == MLX_KEY_LEFT)
		data->player.angle -= 0.1;
	if (keydata.key == MLX_KEY_RIGHT)
		data->player.angle += 0.1;
}

void	handle_keys(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		handle_movement(data, keydata);
		handle_strafe(data, keydata);
		handle_rotation(data, keydata);
	}
}
