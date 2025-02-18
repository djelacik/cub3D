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

#include "cub3D.h"

static int can_move_to(t_data *data, double new_x, double new_y)
{
	// Check four diagonal directions
    double diag_offset;
	
	diag_offset = COLLISION_LIMIT / sqrt(2);
    // Check four cardinal directions
    if (is_wall(data->map, new_x + COLLISION_LIMIT, new_y)) // Right
        return 0;
    if (is_wall(data->map, new_x - COLLISION_LIMIT, new_y)) // Left
        return 0;
    if (is_wall(data->map, new_x, new_y + COLLISION_LIMIT)) // Down
        return 0;
    if (is_wall(data->map, new_x, new_y - COLLISION_LIMIT)) // Up
        return 0;
    if (is_wall(data->map, new_x + diag_offset, new_y + diag_offset)) // Bottom-right
        return 0;
    if (is_wall(data->map, new_x - diag_offset, new_y + diag_offset)) // Bottom-left
        return 0;
    if (is_wall(data->map, new_x + diag_offset, new_y - diag_offset)) // Top-right
        return 0;
    if (is_wall(data->map, new_x - diag_offset, new_y - diag_offset)) // Top-left
        return 0;
    return 1; // No collisions, movement allowed
}

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
        return; // No forward/backward movement

    // Try moving diagonally first
    if (can_move_to(data, new_x, new_y))
    {
        data->player.x = new_x;
        data->player.y = new_y;
    }
    else
    {
        // If blocked, try moving along X only
        if (can_move_to(data, new_x, orig_y))
            data->player.x = new_x;
        // And try moving along Y only
        if (can_move_to(data, orig_x, new_y))
            data->player.y = new_y;
    }
}

static void	handle_rotation(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.angle -= data->player.speed;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.angle += data->player.speed;
}

void my_resize_callback(int width, int height, void* param)
{
	t_data *data = (t_data *)param;

	//debug print
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
}

static void	render(t_data *data)
{
	mlx_delete_image(data->mlx, data->image);
	mlx_resize_hook(data->mlx, &my_resize_callback, (void *)data);
	data->image = mlx_new_image(data->mlx, data->width, data->height);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	draw_floor_and_ceiling(data);
	draw_rays(data);
	draw_mini_map(data);
	draw_mini_player(data);
	draw_mini_rays(data);
}

void	loop_hook(void *param)
{
	t_data	*data;
	data = (t_data *)param;
	handle_movement(data);
	handle_rotation(data);
	render(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}
