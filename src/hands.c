/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hands.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:26:53 by aapadill          #+#    #+#             */
/*   Updated: 2025/03/17 10:27:12 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void draw_hud_hands(t_data *data)
{
	mlx_texture_t	*hand_tex = data->hud_hands[data->hud_frame];

	float			target_height = data->height * 0.6f;
	float			scale_factor = target_height / hand_tex->height;

	int				new_width = hand_tex->width * scale_factor;
	int				new_height = hand_tex->height * scale_factor;

	// bottom center of the screen
	int pos_x = (data->width - new_width) / 2;
	int pos_y = data->height - new_height;

	int y = 0;
	while (y < new_height)
	{
		int x = 0;
		while (x < new_width)
		{
			int	src_x = x / scale_factor;
			int	src_y = y / scale_factor;

			uint32_t color = get_texture_color(hand_tex, src_x, src_y);
			color = simple_shading(color, 1.0);
			// Skip fully transparent pixels (assumes transparency is indicated in the lower 24 bits)
			if ((color & 0xFF000000) != 0)
			{
				mlx_put_pixel(data->image, pos_x + x, pos_y + y, color);
			}
			x++;
		}
		y++;
	}
}
