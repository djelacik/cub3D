/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:01:21 by djelacik          #+#    #+#             */
/*   Updated: 2025/02/21 14:55:18 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <float.h> //erase
# include <assert.h> //erase
# include <fcntl.h> //file open

# include "libft.h"
# include "vec.h"
# include "gc_alloc.h"

# include <MLX42/MLX42.h>

#define GRAY_COLOR 0x444444FF
#define LIGHT_GRAY_COLOR 0xBBBBBBFF
#define RED_COLOR 0xFF0000FF
#define GREEN_COLOR 0x00FF00FF
#define BLUE_COLOR 0x0000FFFF
#define BLUE_COLOR_2 0x00AAFFFF
#define YELLOW_COLOR 0xFFFF00FF
#define BLACK_COLOR 0x000000FF
#define WHITE_COLOR 0xFFFFFFFF
#define SKY_COLOR 0x87CEEBFF
#define FLOOR_COLOR 0x8B4513FF

#define MIN_WIDTH 384
#define MIN_HEIGHT 216
#define MINIMAP_SCALE 0.15
#define TILE_SIZE 64
#define STEP_SIZE 0.5
#define FOV M_PI / 3

#define COLLISION_LIMIT 0.15
#define MOUSE_SENSITIVITY 0.001
#define DOOR_OPENING_SPEED 0.05
#define PLAYER_SPEED 0.00005
#define SEC_PER_FRAME 5
#define PIX_RECOIL 5
#define PIX_WALK 3
#define SHAKE_VEL_WALK 10
#define SHAKE_VEL_RECO 50
#define VEC_INIT_SIZE 4

typedef enum e_door_state{
	CLOSED,
	OPENING,
	OPEN,
	CLOSING
} t_door_state;

typedef struct s_player {
	double		x;
	double		y;
	double		angle;
	double		speed;
}	t_player;

typedef struct s_view {
	int32_t		x;
    int32_t		y;
	int8_t		toggle;
	double		shake_offset;
	double		shake_time;
}	t_view;

typedef struct s_textures {
	mlx_texture_t *north;
	mlx_texture_t *south;
	mlx_texture_t *west;
	mlx_texture_t *east;
	mlx_texture_t *door;
}	t_textures;

typedef struct s_door {
	int				x;
	int				y;
	t_door_state	state;
	double			progress;
}	t_door;

typedef struct s_column {
	int		orig_start_y;
	int		orig_end_y;
	int		vis_start_y;
	int		vis_end_y;
	int		wall_height;
}	t_column;

typedef struct s_dda
{
    int     map_x;
    int     map_y;
    int     step_x;
    int     step_y;
    double  delta_x;
    double  delta_y;
    double  side_x;
    double  side_y;
}   t_dda;

typedef struct s_sprite {
	double	x;
	double	y;
	int		texture;
}	t_sprite;

typedef struct s_map {
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_ray {
	double			distance;
	double			hit_x;
	double			hit_y;
	int				side;
	double			wall_x;
	mlx_texture_t	*texture;
	double			dir_x;
	double			dir_y;
	bool			is_door;
	double			door_progress;
}	t_ray;

typedef struct s_data {
	bool			resize_pending;
    int				new_width;
    int				new_height;

	int				width; //window width
	int				height; //window height
	t_map			map;

	bool 			f_color_found;
	bool			c_color_found;

	mlx_t			*mlx;
	mlx_image_t		*image;
	t_ray			ray;
	t_column		column;
	t_player		player;
	t_view			camera;
	t_textures		*textures;
	uint32_t		floor;
	uint32_t		ceiling;

	t_door			*doors;
	int				door_count;

	t_sprite		*sprites;
	int				num_sprites;
	double			*zBuffer;
	mlx_texture_t	**sprite_textures;

	mlx_texture_t **hud_hands;
	int hud_frame;
	int hud_frame_count;
	int hud_frame_timer;

	bool			is_player_moving;
	bool			is_player_shooting;

	bool			strict;
	char			*error_msg;

	bool			map_started;
	t_vec	map_vec;
}	t_data;

/* 

					CLEAN PROTOTYPES, SOME OF THIS DONT EVEN EXIST ANYMORE 

*/

//file.c
int  	open_cub_file(const char *path);
int  	close_cub_file(int fd, t_data *data);
bool	has_cub_extension(char *filename);

//window.c
bool	init_mlx_data(t_data *data);

//color_utils.c
uint8_t		get_r(uint32_t rgba);
uint8_t		get_g(uint32_t rgba);
uint8_t		get_b(uint32_t rgba);
uint8_t		get_a(uint32_t rgba);
uint32_t	get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

//shading.c
uint32_t	simple_shading(uint32_t color, double distance);

//texture.c
bool			load_texture(char *path, mlx_texture_t **texture);
bool			load_hud_textures(t_data *data);
bool			textures_ready(t_data *data);
uint32_t		get_texture_color(mlx_texture_t *texture, int x, int y);
mlx_texture_t 	*get_wall_texture(t_data *data);

//dda.c
double	calc_delta(double dir);
void	init_dda_axis_x(t_data *data, t_dda *dda, double px, int mx);
void	init_dda_axis_y(t_data *data, t_dda *dda, double py, int my);
bool	process_dda_cell(t_data *data, t_dda *dda);

//ray.c
void	calculate_ray_data(t_data *data, double angle);

//draw_walls.c
double	calculate_corrected_distance(double distance, double ray_angle, double player_angle);
void	draw_wall_column(t_data *data, double angle, int screen_x);
void	draw_walls(t_data *data);
void	draw_wall_texture(t_data *data, int screen_x);
//void	draw_walls_and_sprites(t_data *data);

//movement_utils.c
bool	get_movement_delta(t_data *data, double *dx, double *dy);
void	try_move(t_data *data, double dx, double dy);

//movement.c
void	handle_movement(t_data *data);
void	handle_shake(t_data *data);
void	handle_shooting(t_data *data);
void	handle_rotation(t_data *data);
void	handle_mouse_rotation(t_data *data);

//draw_minimap.c
void	draw_mini_map(t_data *data);
void	draw_mini_player(t_data *data);
void	draw_mini_rays(t_data *data);
void	draw_square(mlx_image_t *image, int x, int y, int size, int color);

//doors.c
double	lookup_door_progress(t_data *data, int x, int y);
void	update_doors(t_data *data);

//callbacks.c
void	my_resize_callback(int width, int height, void* param);

//draw_floor_ceiling.c
void	draw_floor_and_ceiling(t_data *data);

//hooks.c
void	loop_hook(void *param);

//render.c
void	render(t_data *data);

//utils.c
bool	load_texture(char *path, mlx_texture_t **texture);
bool	is_wall(t_data *data, double x, double y); //update
int		can_move_to(t_data *data, double new_x, double new_y);

//line.c
bool	line_is_only_spaces(char *line);
bool	is_map_line(char *line);
bool	split_line(char *line, char **key, char **rest);

//char.c
bool	valid_character(char c);
int		count_char(char *str, char c);
bool	is_number(char *str);

//parsing_head.c
int 	process_header_line(char *line, t_data *data);
bool	parse_color_values(char *str, uint32_t *color);
bool	parse_color_line(char *line, t_data *data);
bool	parse_texture_line(char *line, t_data *data);

//parsing_player.c
bool	parse_player_pos(t_data *data);

//parsing_map.c
bool	build_map(t_data *data, t_vec *map_vec);

//map_algorithms.c
bool 	is_map_closed_strict(t_data *data);
bool	flood_fill(t_data *data, bool **visited, int i, int j);
bool	is_map_closed(t_data *data);

//parsing.c
int		parse_cubfile(char *filepath, t_data *data);

//free.c
void	free_and_exit(void);
void	free_and_exit_with(int exit_code);
void	error_exit(char *msg);
void	free_textures(t_textures *textures);
void	free_hud_textures(t_data *data);

//draw_hands.c
void	draw_hud_hands(t_data *data);
void	shooting_animation(t_data *data);

#endif
