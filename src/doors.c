/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 22:18:28 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/07 22:18:35 by aapadill         ###   ########.fr       */
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

//make smoother, currently it's buggy if moving in a distance == 2
void	update_doors(t_data *data)
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

