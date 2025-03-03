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
	char	cell;

	cell = map[(int)y][(int)x];
	if (cell == '1')
		return (1);
	else if (cell == 'D')
	{
		printf("Door found\n");
		//find door in doors array, need to change args to receive t_data
		return (1);
	}
	return (0);
}

void	draw_floor_and_ceiling(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (y < data->height / 2)
				mlx_put_pixel(data->image, x, y, data->ceiling); // Katon väri
			else
				mlx_put_pixel(data->image, x, y, data->floor); // Lattian väri
			x++;
		}
		y++;
	}
}
