/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 15:40:09 by djelacik          #+#    #+#             */
/*   Updated: 2025/05/21 15:08:08 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//normalize diagonal movement
void	handle_movement(t_data *data)
{
	double	dx;
	double	dy;

	if (!get_movement_delta(data, &dx, &dy))
	{
		data->is_player_moving = false;
		return ;
	}
	try_move(data, dx, dy);
}

void	handle_shake(t_data *data)
{
	if (data->is_player_moving)
	{
		data->camera.shake_time += SEC_PER_FRAME;
		data->camera.shake_offset = sin(data->camera.shake_time
				* SHAKE_VEL_WALK) * PIX_WALK;
		if (data->is_player_shooting)
			data->camera.shake_offset += sin(data->camera.shake_time
					* SHAKE_VEL_RECO) * PIX_RECOIL;
	}
	else if (data->is_player_shooting)
	{
		data->camera.shake_time += SEC_PER_FRAME;
		data->camera.shake_offset = sin(data->camera.shake_time
				* SHAKE_VEL_RECO) * PIX_RECOIL;
	}
	else
	{
		data->camera.shake_time = 0;
		data->camera.shake_offset = 0;
	}
}

void	handle_shooting(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_SPACE))
		data->is_player_shooting = true;
	if (mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
		data->is_player_shooting = true;
}

void	handle_rotation(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.angle -= data->player.speed;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.angle += data->player.speed;
}

void	handle_mouse_rotation(t_data *data)
{
	int32_t	aux_x;
	int32_t	aux_y;
	int32_t	dx;

	aux_x = 0;
	aux_y = 0;
	dx = 0;
	if (mlx_is_key_down(data->mlx, MLX_KEY_TAB))
		data->camera.toggle = 0;
	if (!data->camera.toggle && mlx_is_mouse_down(data->mlx,
			MLX_MOUSE_BUTTON_LEFT))
		data->camera.toggle = 1;
	if (data->camera.toggle == 0)
	{
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
		return ;
	}
	mlx_get_mouse_pos(data->mlx, &aux_x, &aux_y);
	dx = aux_x - data->camera.x;
	if (dx)
		data->player.angle += dx * MOUSE_SENSITIVITY;
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	data->camera.x = data->width / 2;
	data->camera.y = data->height / 2;
	mlx_set_mouse_pos(data->mlx, data->camera.x, data->camera.y);
}
