/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:01:21 by djelacik          #+#    #+#             */
/*   Updated: 2025/01/05 22:38:08 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdlib.h>
# include <stdio.h>

# include "MLX42/MLX42.h"
# include "get_next_line.h"
# include "libft.h"

#define MIN_WIDTH 384
#define MIN_HEIGHT 216
#define MINIMAP_SCALE 0.2
#define TILE_SIZE 64
#define STEP_SIZE 0.01
#define FOV (M_PI / 180) * 90

//# define DEBUG
#ifdef DEBUG 
# define DBG_PRINT(...) fprintf(stderr, __VA_ARGS__)
#else
# define DBG_PRINT(...) ((void)0)
#endif

typedef struct s_player {
	double		x;
	double		y;
	double		angle;
	double		speed;
}	t_player;

typedef struct s_textures {
	mlx_texture_t *north;
	mlx_texture_t *south;
	mlx_texture_t *west;
	mlx_texture_t *east;
}	t_textures;

typedef struct s_ray {
	double			distance;
	double			hit_x;
	double			hit_y;
	int				side;
	double			wall_x;
	mlx_texture_t	*texture;
	double			dir_x;
	double			dir_y;
}	t_ray;

typedef struct s_data {
	int 		width;
	int 		height;
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_ray		*ray;
	t_player	player;
	t_textures	*textures;
	char		**map;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
}	t_data;

//color_utils.c
uint8_t	get_r(uint32_t rgba);
uint8_t	get_g(uint32_t rgba);
uint8_t	get_b(uint32_t rgba);
uint8_t	get_a(uint32_t rgba);
uint32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

//shading.c
uint32_t	simple_shading(uint32_t color, double distance);

//texture.c
uint32_t	get_texture_color(mlx_texture_t *texture, int x, int y);
mlx_texture_t *get_wall_texture(t_data *data, double dir_x, double dir_y, int side);
void	draw_wall_texture(t_data *data, t_ray *ray, int screen_x, int start_y, int end_y);
//void	draw_wall_pattern_texture(t_data *data, t_ray *ray, int screen_x, int start_y, int end_y);
void	draw_wall_pattern_texture(t_data *data, t_ray *ray, int screen_x, int start_y, int end_y, double scale);

//ray.c
double	calculate_distance(t_player player, double angle, char **map, t_ray *ray);
int		calculate_hit_side(t_player player, double angle, char **map);
double	get_wall_x(double hit_x, double hit_y, int hit_side);
t_ray	calculate_ray(t_data *data, double angle);

//rays.c
double	calculate_corrected_distance(double distance, double ray_angle, double player_angle);
void	draw_single_ray(t_data *data, double angle, int screen_x);
void	draw_rays(t_data *data);

//movement.c
void	loop_hook(void *param);

//minimap.c
void	draw_mini_map(t_data *data);
void	draw_mini_player(t_data *data);
void	draw_mini_rays(t_data *data);
void	draw_square(mlx_image_t *image, int x, int y, int size, int color);

//utils.c
int		is_wall(char **map, double x, double y);
void	draw_floor_and_ceiling(t_data *data);

//void	handle_keys(mlx_key_data_t keydata, void *param);
//int	load_textures(t_data *data);

#endif