/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 02:09:45 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/08 02:09:51 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	loop_hook(void *param)
{
	t_data	*data;
	data = (t_data *)param;

	handle_movement(data);
	handle_shake(data);
	handle_shooting(data);
	handle_mouse_rotation(data);
	handle_rotation(data);
	render(data);
	update_doors(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}
