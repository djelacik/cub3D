/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hands.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:26:53 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/21 15:01:51 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_hud_hands(t_data *data)
{
	mlx_texture_t	*hand_tex;
	float			sf;
	int				y;
	int				x;
	uint32_t		color;

	hand_tex = data->hud_hands[data->hud_frame];
	sf = (data->height * 0.6f) / hand_tex->height;
	y = 0;
	while (y < hand_tex->height * sf)
	{
		x = 0;
		while (x < hand_tex->width * sf)
		{
			color = get_texture_color(hand_tex, x / sf, y / sf);
			if ((color & 0x00FFFFFF) != 0)
			{
				color = shading(color, 1.0);
				mlx_put_pixel(data->image, (data->width - hand_tex->width * sf)
					/ 2 + x, data->height - hand_tex->height * sf + y, color);
			}
			x++;
		}
		y++;
	}
}

void	shooting_animation(t_data *data)
{
	bool	just_started;

	if (data->is_player_shooting)
	{
		just_started = true;
		data->hud_frame_timer++;
		if (data->hud_frame_timer >= SEC_PER_FRAME)
		{
			data->hud_frame = (data->hud_frame + 1) % data->hud_frame_count;
			data->hud_frame_timer = 0;
			just_started = false;
		}
		if (data->hud_frame == 0 && !just_started)
			data->is_player_shooting = 0;
	}
	else
	{
		data->hud_frame = 0;
		data->hud_frame_timer = 0;
	}
}
