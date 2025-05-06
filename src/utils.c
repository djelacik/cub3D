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

bool	load_texture(char *path, mlx_texture_t **texture)
{
	*texture = mlx_load_png(path);
	if (!*texture)
		return (false);
	return (true);
}

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

//make smoother, currently it's buggy if moving in a distance == 2
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
		if (distance < 3) /* adjust threshold */
		{
			// Check the angle between player direction and the door
			// (For simplicity, you might compare the player's angle with the angle to the door)
			// If conditions are met, start opening:
			if (door->state == CLOSED)
			{
				door->state = OPENING;
			}
		}
		
		// Animate door opening/closing
		if (door->state == OPENING)
		{
			door->progress += DOOR_OPENING_SPEED; // adjust speed as needed
			if (door->progress > 1.0)
			{
				door->progress = 1.01;
				door->state = OPEN;
			}
		}
		else if (door->state == OPEN)
		{
			// Optionally, if the player moves away, start closing the door
			if (distance > 3)
				door->state = CLOSING;
		}
		else if (door->state == CLOSING)
		{
			door->progress -= DOOR_OPENING_SPEED;
			if (door->progress <= 0.0)
			{
				door->progress = 0.0;
				door->state = CLOSED;
			}
		}
		i++;
	}
}

static char	get_map_cell(t_data *data, double x, double y)
{
	int	xi;
	int	yi;

	xi = (int)x;
	yi = (int)y;
	if (yi < 0 || yi >= data->map.height)
		return ('1');
	if (xi < 0 || xi >= (int)ft_strlen(data->map.grid[yi]))
		return ('1');
	return (data->map.grid[yi][xi]);
}

bool	is_wall(t_data *data, double x, double y)
{
	char	cell;

	cell = get_map_cell(data, x, y);
	if (cell == '1')
		return (1);
	else if (cell == 'D')
	{
		int i = 0;
		while (i < data->door_count)
		{
			if (data->doors[i].x == (int)x && data->doors[i].y == (int)y)
			{
				// If door is closed or only partially open, consider it a wall
				if (data->doors[i].state == CLOSED || data->doors[i].progress < 0.8)
					return (true);
				else
					return (false);
			}
			i++;
		}
		return (true);
	}
	return (false);
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