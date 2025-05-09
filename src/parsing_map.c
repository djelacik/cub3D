/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:29:25 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/08 14:29:26 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//TODO
bool	build_map(t_data *data, t_vec *map_vec)
{
	size_t	i;
	int		row_len;
	int		doors;

	doors = 0;
	data->map.height = map_vec->len;
	data->map.grid = gc_alloc((map_vec->len + 1) * sizeof(char *));
	if (!data->map.grid)
	{
		data->error_msg = "Map alloc failed";
		return (1);
	}
	else
	{
		i = 0;
		while (i < map_vec->len)
		{
			data->map.grid[i] = *(char **)vec_get(map_vec, i);
			/*should this be here?*/
			int j = 0;
			while (data->map.grid[i][j])
			{
				if (data->map.grid[i][j] == 'D')
				{
					doors++;
				}
				j++;
			}
			/*should this be here?*/
			row_len = ft_strlen(data->map.grid[i]);
			if (row_len > data->map.width)
				data->map.width = row_len;
			i++;
		}
		if (doors > 0)
		{
			data->doors = gc_alloc(doors * sizeof(t_door));
			ft_memset(data->doors, 0, doors * sizeof(t_door));
		}
		else
		{
			data->doors = NULL;
		}
		data->map.grid[map_vec->len] = NULL;
		return (0);
	}
}

