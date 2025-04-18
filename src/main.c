/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:02:56 by djelacik          #+#    #+#             */
/*   Updated: 2025/01/04 18:56:34 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

//try many doors
//use argv[1] as cubfile
bool	initializer(t_data *data, char *filename)
{
	int	monitor_width;
	int	monitor_height;
	int	status;

	status = 0;
	ft_memset(data, 0, sizeof(t_data));
	data->player.speed = 0.025;
	data->mlx = mlx_init(MIN_WIDTH, MIN_HEIGHT, "Cub3D Ray-Casting", true);
	if (!data->mlx)
		return (EXIT_FAILURE);
	data->textures = gc_alloc(sizeof(t_textures));
	if (!data->textures)
	{
		printf("Error: Failed to allocate memory for textures\n");
		return (EXIT_FAILURE);
	}
	ft_memset(data->textures, 0, sizeof(t_textures));
	data->textures->door = mlx_load_png("textures/pics/eagle.png");
	status = parse_cubfile(filename, data);
	if (status)
	{
		printf("Parsing error\n");
		//mlx_terminate(data->mlx); //if window
		if (data->textures)
			free_textures(data->textures);
		return (EXIT_FAILURE);
	}
	mlx_get_monitor_size(0, &monitor_width, &monitor_height);
	data->width = monitor_width * 0.5;
	data->height = monitor_height * 0.5;
	mlx_set_window_size(data->mlx, data->width, data->height);
	mlx_set_window_limit(data->mlx, MIN_WIDTH, MIN_HEIGHT, monitor_width, monitor_height);
	mlx_set_window_pos(data->mlx, (monitor_width - data->width) / 2, (monitor_height - data->height) / 2);
	data->camera.x = data->width / 2;
	data->camera.y = data->height / 2;
	data->image = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->image)
		return (EXIT_FAILURE);
	/* sprite hardcoded try */
	data->sprites = gc_alloc(sizeof(t_sprite) * 3);
	data->num_sprites = 3;
	data->sprites[0].x = 2.5;
	data->sprites[0].y = 2.5;
	data->sprites[0].texture = 0;
	data->sprites[1].x = 5.5;
	data->sprites[1].y = 5.5;
	data->sprites[1].texture = 1;
	data->sprites[2].x = 2.5;
	data->sprites[2].y = 5.5;
	data->sprites[2].texture = 2;
	data->zBuffer = gc_alloc(sizeof(double) * data->width);
	data->sprite_textures = gc_alloc(sizeof(mlx_texture_t *) * 3);
	data->sprite_textures[0] = mlx_load_png("textures/pics/pillar.png");
	data->sprite_textures[1] = mlx_load_png("textures/pics/greenlight.png");
	data->sprite_textures[2] = mlx_load_png("textures/pics/barrel.png");
	/* sprite hardcoded try */

	/* hands */
	data->hud_hands = gc_alloc(sizeof(mlx_texture_t *) * 5);
	data->hud_hands[0] = mlx_load_png("textures/hand/hand111.png");
	data->hud_hands[1] = mlx_load_png("textures/hand/hand222.png");
	data->hud_hands[2] = mlx_load_png("textures/hand/hand333.png");
	data->hud_hands[3] = mlx_load_png("textures/hand/hand444.png");
	data->hud_hands[4] = mlx_load_png("textures/hand/hand555.png");
	data->hud_frame_count = 5;
	/* hands */
	if (is_wall(data, data->player.x, data->player.y))
	{
		printf("Error: Player starts inside a wall\n");
		mlx_terminate(data->mlx);
		free_textures(data->textures);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		error;
	
	if (argc != 2)
	{
		printf("Usage: %s <.cub file>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	error = initializer(&data, argv[1]);
	if (error)
		return (EXIT_FAILURE);
	mlx_image_to_window(data.mlx, data.image, 0, 0);
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_textures(data.textures);
	mlx_delete_texture(data.sprite_textures[0]);
	mlx_delete_texture(data.sprite_textures[1]);
	mlx_delete_texture(data.sprite_textures[2]);
	mlx_delete_texture(data.hud_hands[0]);
	mlx_delete_texture(data.hud_hands[1]);
	mlx_delete_texture(data.hud_hands[2]);
	mlx_delete_texture(data.hud_hands[3]);
	mlx_delete_texture(data.hud_hands[4]);
	//gc_free(data.textures);
	gc_free_all();
	return (EXIT_SUCCESS);
}
