/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:01:21 by djelacik          #+#    #+#             */
/*   Updated: 2025/01/02 16:37:47 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "MLX42/MLX42.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define WIN_WIDTH 1800
#define WIN_HEIGHT 1600
#define TILE_SIZE 64
#define STEP_SIZE 0.1
#define FOV (M_PI / 3)

//# define DEBUG
#ifdef DEBUG 
# define dbg_print(...) fprintf(stderr, __VA_ARGS__)
#else
# define dbg_print(...) ((void)0)
#endif

typedef struct s_player {
	double		x;
	double		y;
	double		angle;
}	t_player;

typedef struct s_data {
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_player	player;
	char		**map;
}	t_data;

void	handle_keys(mlx_key_data_t keydata, void *param);
int		is_wall(char **map, double x, double y);

#endif