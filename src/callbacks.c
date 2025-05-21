/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 23:09:35 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/21 14:57:36 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//printf("Reached smallest resolution: %i x %i\n", width, height);
//printf("Resize Callback: new dimensions set to %i x %i\n", 
//data->new_width, data->new_height);
void	my_resize_callback(int width, int height, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (width <= MIN_WIDTH || height <= MIN_HEIGHT)
	{
		if (width == MIN_WIDTH && height == MIN_HEIGHT)
		{
			return ;
		}
		if (width <= MIN_WIDTH)
			data->new_width = MIN_WIDTH;
		else
			data->new_width = width;
		if (height <= MIN_HEIGHT)
			data->new_height = MIN_HEIGHT;
		else
			data->new_height = height;
	}
	else
	{
		data->new_width = width;
		data->new_height = height;
	}
	data->resize_pending = true;
}
