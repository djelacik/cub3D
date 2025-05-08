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
	int i;

	i = 0;
	while (i < data->door_count)
	{
		if (data->doors[i].x == x && data->doors[i].y == y)
			return data->doors[i].progress;
		i++;
	}
	return 0;
}

void	update_door_state(t_door *door, double distance)
{
	if (distance < 3 && door->state == CLOSED)
		door->state = OPENING;
	if (door->state == OPENING)
	{
		door->progress += DOOR_OPENING_SPEED;
		if (door->progress > 1.0)
		{
			door->progress = 1.01;
			door->state = OPEN;
		}
	}
	else if (door->state == OPEN && distance > 3)
		door->state = CLOSING;
	else if (door->state == CLOSING)
	{
		door->progress -= DOOR_OPENING_SPEED;
		if (door->progress <= 0.0)
		{
			door->progress = 0.0;
			door->state = CLOSED;
		}
	}
}

//make smoother, currently it's buggy if moving in a distance == 2
void	update_doors(t_data *data)
{
	int		i;
	t_door 	*door;
	double 	dx;
	double 	dy;
	double 	distance;

	i = 0;
	while (i < data->door_count)
	{
		door = &data->doors[i];
		dx = door->x + 0.5 - data->player.x;
		dy = door->y + 0.5 - data->player.y;
		distance = sqrt(dx * dx + dy * dy);
		update_door_state(door, distance);
		i++;
	}
}
