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
	mlx_texture_t *hand_tex = data->hud_hands[data->hud_frame];

	// bottom center of the screen
	int pos_x = (data->width - hand_tex->width) / 2;
	int pos_y = data->height - hand_tex->height;

	uint32_t y = 0;
	while (y < hand_tex->height)
	{
		uint32_t x = 0;
		while (x < hand_tex->width)
		{
			uint32_t color = get_texture_color(hand_tex, x, y);
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

