/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:34:31 by djelacik          #+#    #+#             */
/*   Updated: 2025/01/04 18:53:55 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_wall(char **map, double x, double y)
{
	if (map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

void	draw_floor_and_ceiling(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (y < WIN_HEIGHT / 2)
				mlx_put_pixel(data->image, x, y, data->ceiling_color); // Katon väri
			else
				mlx_put_pixel(data->image, x, y, data->floor_color); // Lattian väri
			x++;
		}
		y++;
	}
}
