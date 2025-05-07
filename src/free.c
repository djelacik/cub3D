/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:15:42 by aapadill          #+#    #+#             */
/*   Updated: 2025/02/24 15:16:13 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//clean textures too
//terminate window
void	free_and_exit(void)
{
	gc_free_all();
	exit(EXIT_FAILURE);
}

void	free_and_exit_with(int exit_code)
{
	gc_free_all();
	exit(exit_code);
}

void	error_exit(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	gc_free_all();
	exit(EXIT_FAILURE);
}

void	free_textures(t_textures *textures)
{
	if (textures->north)
		mlx_delete_texture(textures->north);
	if (textures->south)
		mlx_delete_texture(textures->south);
	if (textures->west)
		mlx_delete_texture(textures->west);
	if (textures->east)
		mlx_delete_texture(textures->east);
	if (textures->door)
		mlx_delete_texture(textures->door);
}

void	free_hud_textures(t_data *data)
{
	int	i;

	if (data->hud_hands)
	{
		i = 0;
		while (i < data->hud_frame_count)
		{
			if (data->hud_hands[i])
				mlx_delete_texture(data->hud_hands[i]);
			i++;
		}
		gc_free(data->hud_hands);
		data->hud_frame_count = 0;
		data->hud_hands = NULL;
	}
}