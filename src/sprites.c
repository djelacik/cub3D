/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 22:41:52 by aapadill          #+#    #+#             */
/*   Updated: 2025/03/08 22:42:09 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* ----------------------------------------------------------------------------
   sort_sprites
   ----------------------------------------------------------------------------
   Given an array of sprite indices (order) and their corresponding distance
   values (dist), this function sorts the indices so that the sprites are
   ordered from farthest to nearest.
   For a small number of sprites, a simple bubble sort suffices.
---------------------------------------------------------------------------- */
static void	sort_sprites(int *order, double *dist, int num)
{
	int		i;
	int		j;
	int		tmp_order;
	double	tmp_dist;

	i = 0;
	while (i < num)
	{
		j = 0;
		while (j < num - 1)
		{
			if (dist[j] < dist[j + 1])
			{
				tmp_dist = dist[j];
				dist[j] = dist[j + 1];
				dist[j + 1] = tmp_dist;
				tmp_order = order[j];
				order[j] = order[j + 1];
				order[j + 1] = tmp_order;
			}
			j++;
		}
		i++;
	}
}

/* ----------------------------------------------------------------------------
   render_sprites
   ----------------------------------------------------------------------------
   This function renders all the sprites. It:
     1. Computes each sprite's distance from the player.
     2. Sorts the sprites from farthest to nearest.
     3. Projects each sprite into camera space using the inverse of the 2x2
        camera matrix, which is computed from the player's direction and the
        camera plane.
     4. Computes the sprite’s on-screen size and drawing boundaries.
     5. Draws each sprite stripe by stripe, but only draws a pixel if:
          - The sprite is in front of the camera.
          - The current stripe is within the screen bounds.
          - The sprite is closer than the wall (using the 1D ZBuffer).
---------------------------------------------------------------------------- */

void	render_sprites(t_data *data)
{
	int		*sprite_order;
	double	*sprite_distance;

	if (data->num_sprites <= 0)
		return ;
	sprite_order = malloc(sizeof(int) * data->num_sprites);
	sprite_distance = malloc(sizeof(double) * data->num_sprites);
	if (!sprite_order || !sprite_distance)
		return ; //implement error handling
	// Compute squared distances from the player for each sprite
	int i = 0;
	while (i < data->num_sprites)
	{
		sprite_order[i] = i;
		double dx = data->player.x - data->sprites[i].x;
		double dy = data->player.y - data->sprites[i].y;
		sprite_distance[i] = dx * dx + dy * dy;
		i++;
	}
	sort_sprites(sprite_order, sprite_distance, data->num_sprites);
	// Compute camera parameters
	double dir_x = cos(data->player.angle);
	double dir_y = sin(data->player.angle);
	double plane_x = -dir_y * tan(FOV / 2);
	double plane_y = dir_x * tan(FOV / 2);
	// Loop through all sprites in sorted order (from farthest to nearest)
	i = 0;
	while (i < data->num_sprites)
	{
		int index = sprite_order[i];
		t_sprite *spr = &data->sprites[index];
		// Translate sprite position to relative coordinates to the player
		double sprite_x = spr->x - data->player.x;
		double sprite_y = spr->y - data->player.y;
		// Transform sprite with the inverse camera matrix
		double inv_det = 1.0 / (plane_x * dir_y - dir_x * plane_y);
		double transform_x = inv_det * (dir_y * sprite_x - dir_x * sprite_y);
		double transform_y = inv_det * (-plane_y * sprite_x + plane_x * sprite_y);
		// TransformY is the sprite's depth in camera space
		// Calculate sprite's screen X coordinate
		int sprite_screen_x = (int)((data->width / 2) * (1 + transform_x / transform_y));
		// Calculate height of the sprite on screen
		int sprite_height = abs((int)(data->height / transform_y));
		int draw_start_y = -sprite_height / 2 + data->height / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		int draw_end_y = sprite_height / 2 + data->height / 2;
		if (draw_end_y >= data->height)
			draw_end_y = data->height - 1;
		// Calculate width of the sprite
		int sprite_width = abs((int)(data->height / transform_y));
		int draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		int draw_end_x = sprite_width / 2 + sprite_screen_x;
		if (draw_end_x >= data->width)
			draw_end_x = data->width - 1;
		// Loop through every vertical stripe of the sprite on screen
		int stripe = draw_start_x;
		while (stripe < draw_end_x)
		{
			mlx_texture_t *tex = data->sprite_textures[spr->texture];
			int tex_x = (int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * tex->width / sprite_width) / 256;
			// Proceed if the sprite is in front of the camera and the stripe is on screen,
			// and if the sprite is closer than the wall at this stripe (using the ZBuffer)
			if (transform_y > 0 && stripe >= 0 && stripe < data->width && transform_y < data->zBuffer[stripe])
			{
				int y = draw_start_y;
				while (y < draw_end_y)
				{
					int d = (y) * 256 - data->height * 128 + sprite_height * 128;
					int tex_y = ((d * tex->height) / sprite_height) / 256;
					uint32_t color = get_texture_color(tex, tex_x, tex_y);
					    if ((color & 0x00FFFFFF) != 0)
						{
							// Get channels using your color utils.
							uint8_t a = get_a(color);
							uint8_t orig_r = get_r(color);
							uint8_t g = get_g(color);
							uint8_t orig_b = get_b(color);
							// Swap red and blue channels
							uint8_t r = orig_b;
							uint8_t b = orig_r;
							uint32_t fixed_color = get_rgba(r, g, b, a);
							mlx_put_pixel(data->image, stripe, y, fixed_color);
						}
					y++;
				}
			}
			stripe++;
		}
		i++;
	}
	free(sprite_order);
	free(sprite_distance);
}
