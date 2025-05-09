/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:37:31 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/09 14:37:32 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	get_movement_delta(t_data *data, double *dx, double *dy)
{
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        *dx = cos(data->player.angle) * data->player.speed;
        *dy = sin(data->player.angle) * data->player.speed;
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        *dx = -cos(data->player.angle) * data->player.speed;
        *dy = -sin(data->player.angle) * data->player.speed;
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        *dx = -sin(data->player.angle) * data->player.speed;
        *dy = cos(data->player.angle) * data->player.speed;
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        *dx = sin(data->player.angle) * data->player.speed;
        *dy = -cos(data->player.angle) * data->player.speed;
    }
    else
        return (false);
    return (true);
}

void	try_move(t_data *data, double dx, double dy)
{
    double  x;
    double  y;

    x = data->player.x;
    y = data->player.y;
    if (can_move_to(data, x + dx, y + dy))
    {
        data->player.x = x + dx;
        data->player.y = y + dy;
        data->is_player_moving = true;
    }
    else
    {
        if (can_move_to(data, x + dx, y))
        {
            data->player.x = x + dx;
            data->is_player_moving = true;
        }
        if (can_move_to(data, x, y + dy))
        {
            data->player.y = y + dy;
            data->is_player_moving = true;
        }
    }
}
