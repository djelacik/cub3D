/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 15:40:09 by djelacik          #+#    #+#             */
/*   Updated: 2025/03/13 17:52:11 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int can_move_to(t_data *data, double new_x, double new_y)
{
	// Check four diagonal directions
	double diag_offset;

	diag_offset = COLLISION_LIMIT / sqrt(2);
	// Check four cardinal directions
	if (is_wall(data, new_x + COLLISION_LIMIT, new_y)) // Right
		return 0;
	if (is_wall(data, new_x - COLLISION_LIMIT, new_y)) // Left
		return 0;
	if (is_wall(data, new_x, new_y + COLLISION_LIMIT)) // Down
		return 0;
	if (is_wall(data, new_x, new_y - COLLISION_LIMIT)) // Up
		return 0;
	if (is_wall(data, new_x + diag_offset, new_y + diag_offset)) // Bottom-right
		return 0;
	if (is_wall(data, new_x - diag_offset, new_y + diag_offset)) // Bottom-left
		return 0;
	if (is_wall(data, new_x + diag_offset, new_y - diag_offset)) // Top-right
		return 0;
	if (is_wall(data, new_x - diag_offset, new_y - diag_offset)) // Top-left
		return 0;
	return 1; // No collisions, movement allowed
}

//normalize diagonal movement
static void handle_movement(t_data *data)
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

static void	handle_rotation(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.angle -= data->player.speed;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.angle += data->player.speed;
}

static void handle_mouse_rotation(t_data *data)
{
	int32_t aux_x = 0;
	int32_t aux_y = 0;
	int32_t dx = 0;
	//int32_t dy = 0;
	
	// if (!data->flag)
	// {
	// 	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	// 	return ;
	// }
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

void my_resize_callback(int width, int height, void* param)
{
	t_data *data = (t_data *)param;

	// if (!data->flag)
	// {
	// 	data->flag = 1;
	// 	data->camera.toggle = 1;
	// 	//mlx_set_cursor_mode(data->mlx, MLX_MOUSE_NORMAL);
	// }
	printf("Window resized to %dx%d\n", data->width, data->height);
	if (width <= MIN_WIDTH || height <= MIN_HEIGHT)
	{
		if (width == MIN_WIDTH && height == MIN_HEIGHT)
			printf("Reached smallest resolution: %i x %i\n", width, height);
		//mlx_set_window_size(data->mlx, data->width, data->height);
		if (width <= MIN_WIDTH)
			data->width = MIN_WIDTH;
		else
			data->width = width;
		if (height <= MIN_HEIGHT)
			data->height = MIN_HEIGHT;
		else
			data->height = height;
		return ;
	}
	data->width = width;
	data->height = height;
	data->player.speed = (double)height * 0.00002;
	free(data->zBuffer);
	data->zBuffer = malloc(sizeof(double) * data->width);
}

static void	render(t_data *data)
{
	mlx_delete_image(data->mlx, data->image);
	mlx_resize_hook(data->mlx, &my_resize_callback, (void *)data);
	data->image = mlx_new_image(data->mlx, data->width, data->height);
	mlx_image_to_window(data->mlx, data->image, 0, 0);

	draw_floor_and_ceiling(data);
	//draw_walls(data);
	//draw_sprites(data);
	draw_walls_and_sprites(data);
	draw_mini_map(data);
	draw_mini_player(data);
	draw_mini_rays(data);

	// Draw HUD hands
	draw_hud_hands(data);
    // Hud animation
	if (data->is_player_moving)
	{
		data->hud_frame_timer++;
		if (data->hud_frame_timer >= 5)
		{
			data->hud_frame = (data->hud_frame + 1) % data->hud_frame_count;
			data->hud_frame_timer = 0;
		}
	}
	else
	{
		data->hud_frame = 0;
		data->hud_frame_timer = 0;
	}
}

void	loop_hook(void *param)
{
	t_data	*data;
	data = (t_data *)param;

	handle_movement(data);
	handle_mouse_rotation(data);
	handle_rotation(data);
	render(data);
	update_doors(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}
