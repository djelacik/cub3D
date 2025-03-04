/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:34:31 by djelacik          #+#    #+#             */
/*   Updated: 2025/03/04 14:44:23 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	lookup_door_progress(t_data *data, int x, int y)
{
	int i = 0;
	while (i < data->door_count)
	{
		if (data->doors[i].x == x && data->doors[i].y == y)
			return data->doors[i].progress;
		i++;
	}
	return 0;
}

void update_doors(t_data *data)
{
	int	i = 0;
	while (i < data->door_count)
	{
		t_door *door = &data->doors[i];
		double dx = door->x + 0.5 - data->player.x;
		double dy = door->y + 0.5 - data->player.y;
		double distance = sqrt(dx * dx + dy * dy);
		
		// If player is close enough and roughly facing the door, trigger it
		if (distance < 2 /* adjust threshold */)
		{
			// Check the angle between player direction and the door
			// (For simplicity, you might compare the player's angle with the angle to the door)
			// If conditions are met, start opening:
			if (door->state == CLOSED)
				door->state = OPENING;
		}
		
		// Animate door opening/closing
		if (door->state == OPENING)
		{
			door->progress += 0.02; // adjust speed as needed
			if (door->progress >= 1.0)
			{
				door->progress = 1.0;
				door->state = OPEN;
			}
		}
		else if (door->state == OPEN)
		{
			// Optionally, if the player moves away, start closing the door
			if (distance > 2)
				door->state = CLOSING;
		}
		else if (door->state == CLOSING)
		{
			door->progress -= 0.02;
			if (door->progress <= 0.0)
			{
				door->progress = 0.0;
				door->state = CLOSED;
			}
		}
		i++;
	}
}


int	is_wall(t_data *data, double x, double y)
{
	char	cell;

	cell = data->map.grid[(int)y][(int)x];
	if (cell == '1')
		return (1);
	else if (cell == 'D')
	{
		int i = 0;
		while (i < data->door_count)
		{
			if (data->doors[i].x == (int)x && data->doors[i].y == (int)y)
			{
				// If door is closed or only partially open, consider it a wall.
				if (data->doors[i].state == CLOSED || data->doors[i].progress < 0.8)
					return (1);
				else
					return (0);
			}
			i++;
		}
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
