/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 15:40:09 by djelacik          #+#    #+#             */
/*   Updated: 2025/04/14 10:20:25 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//normalize diagonal movement
void handle_movement(t_data *data)
{
	double orig_x;
	double orig_y;
	double new_x;
	double new_y;

	orig_x = data->player.x;
	orig_y = data->player.y;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		new_x = orig_x + cos(data->player.angle) * data->player.speed;
		new_y = orig_y + sin(data->player.angle) * data->player.speed;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		new_x = orig_x - cos(data->player.angle) * data->player.speed;
		new_y = orig_y - sin(data->player.angle) * data->player.speed;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		new_x = orig_x - sin(data->player.angle) * data->player.speed;
		new_y = orig_y + cos(data->player.angle) * data->player.speed;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		new_x = orig_x + sin(data->player.angle) * data->player.speed;
		new_y = orig_y - cos(data->player.angle) * data->player.speed;
	}
	else
	{
		data->is_player_moving = false;
		return; // No forward/backward movement
	}

	// Try moving diagonally first
	if (can_move_to(data, new_x, new_y))
	{
		data->player.x = new_x;
		data->player.y = new_y;
		data->is_player_moving = true;
	}
	else
	{
		// If blocked, try moving along X only
		if (can_move_to(data, new_x, orig_y))
		{
			data->player.x = new_x;
			data->is_player_moving = true;
		}
		// And try moving along Y only
		if (can_move_to(data, orig_x, new_y))
		{
			data->player.y = new_y;
			data->is_player_moving = true;
		}
	}
}

void handle_shake(t_data *data)
{
	if (data->is_player_moving)
	{
		data->camera.shake_time += SEC_PER_FRAME;
		data->camera.shake_offset = sin(data->camera.shake_time * SHAKE_VEL_WALK) * PIX_WALK;
		if (data->is_player_shooting)
			data->camera.shake_offset += sin(data->camera.shake_time * SHAKE_VEL_RECO) * PIX_RECOIL;
		//printf("Shake time: %f\n", data->camera.shake_time);
	}
	else if (data->is_player_shooting)
	{
		data->camera.shake_time += SEC_PER_FRAME;
		data->camera.shake_offset = sin(data->camera.shake_time * SHAKE_VEL_RECO) * PIX_RECOIL;
		//printf("Shake time: %f\n", data->camera.shake_time);
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

void handle_mouse_rotation(t_data *data)
{
	int32_t aux_x = 0;
	int32_t aux_y = 0;
	int32_t dx = 0;

	if (mlx_is_key_down(data->mlx, MLX_KEY_TAB))
		data->camera.toggle = 0;
	if (!data->camera.toggle && mlx_is_mouse_down(data->mlx, MLX_MOUSE_BUTTON_LEFT))
		data->camera.toggle = 1;
	if (data->camera.toggle == 0)
	{
		mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
		return ;
	}
	mlx_get_mouse_pos(data->mlx, &aux_x, &aux_y);
	dx = aux_x - data->camera.x;
	//dy = aux_y - data->camera.y;
	if (dx)
		data->player.angle += dx * MOUSE_SENSITIVITY;
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	data->camera.x = data->width / 2;
	data->camera.y = data->height / 2;
	mlx_set_mouse_pos(data->mlx, data->camera.x, data->camera.y);
}
