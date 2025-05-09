/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 14:34:59 by aapadill          #+#    #+#             */
/*   Updated: 2025/05/08 14:34:59 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_player(t_data *data, char c, int i, int j)
{
    if (c == 'N')
        data->player.angle = 3 * M_PI / 2;
    else if (c == 'S')
        data->player.angle = M_PI / 2;
    else if (c == 'E')
        data->player.angle = 0;
    else
        data->player.angle = M_PI;
    data->player.x = j + 0.5;
    data->player.y = i + 0.5;
    data->map.grid[i][j] = '0';
}

static bool	process_cell_content(t_data *data, char c, int i, int j)
{
    if (c == 'D')
    {
        if (!data->textures->door)
        {
            data->error_msg = "Door texture not defined";
            return (true);
        }
        data->doors[data->door_count].x = j;
        data->doors[data->door_count].y = i;
        data->doors[data->door_count].state = CLOSED;
        data->doors[data->door_count].progress = 0;
        data->door_count++;
    }
    else if (c == ' ')
        data->map.grid[i][j] = '0';
    else if (c != '0' && c != '1')
    {
        data->error_msg = "Invalid character in map";
        return (true);
    }
    return (false);
}

static bool	classify_cell(t_data *data, bool *assigned, int i, int j)
{
    char c;

    c = data->map.grid[i][j];
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
    {
        if (!*assigned)
        {
            init_player(data, c, i, j);
            *assigned = true;
        }
        else
        {
            data->error_msg = "Multiple player positions detected";
            return (true);
        }
    }
    else
    {
        if (process_cell_content(data, c, i, j))
            return (true);
    }
    return (false);
}

bool	parse_player_pos(t_data *data)
{
    int  i;
    int  j;
    bool assigned;

    assigned = false;
    i = 0;
    while (data->map.grid[i])
    {
        j = 0;
        while (data->map.grid[i][j])
        {
            if (classify_cell(data, &assigned, i, j))
                return (true);
            j++;
        }
        i++;
    }
    if (!assigned)
    {
        data->error_msg = "No player position found";
        return (true);
    }
    return (false);
}
