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

/*
char	**init_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 11);
	if (!map)
		return (NULL);
	map[0] = "1111111111";
	map[1] = "1000000001";
	map[2] = "1000000001";
	map[3] = "1001001001";
	map[4] = "1001001001";
	map[5] = "1000000001";
	map[6] = "1001111101";
	map[7] = "1000000001";
	map[8] = "1111111111";
	map[9] = NULL;

	// Tulosta kartan sisältö
	int y = 0;
	while (map[y])
	{
		printf("Map row %d: %s\n", y, map[y]);
		y++;
	}

	return (map);
}

int	load_textures(t_data *data)
{
	data->textures->north = mlx_load_png("textures/wall64px.png");
	//data->textures->south = mlx_load_png("textures/pics/bluestone.png");
	data->textures->south = mlx_load_png("textures/pics/spruce.png");
	data->textures->west = mlx_load_png("textures/pics/colorstone.png");
	data->textures->east = mlx_load_png("textures/pics/greystone.png");

	// Tarkista, onnistuiko kaikkien tekstuurien lataus
	if (!data->textures->north)
		fprintf(stderr, "Error: Failed to load north texture\n");
	if (!data->textures->south)
		fprintf(stderr, "Error: Failed to load south texture\n");
	if (!data->textures->west)
		fprintf(stderr, "Error: Failed to load west texture\n");
	if (!data->textures->east)
		fprintf(stderr, "Error: Failed to load east texture\n");
	return (0);
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
}
*/

int	main(void)
{
	t_data	data;
	int		monitor_width;
	int		monitor_height;

	//data.map = init_map();
	//if (!data.map)
	//	return (1);
	ft_memset(&data, 0, sizeof(t_data));
	/*
		assign N, S, W, E to player.angle and set player.x, player.y
	*/
	data.player.x = 2;
	data.player.y = 2;
	//data.camera.x = 0;
	//data.camera.y = 0;
	data.camera.toggle = 1;
	//data.player.angle = 0.0;
	data.player.speed = 0.01;
	data.mlx = mlx_init(MIN_WIDTH, MIN_HEIGHT, "Cub3D Ray-Casting", true);
	mlx_get_monitor_size(0, &monitor_width, &monitor_height);
	data.width = monitor_width * 0.5;
	data.height = monitor_height * 0.5;
	mlx_set_window_size(data.mlx, data.width, data.height);
	mlx_set_window_limit(data.mlx, MIN_WIDTH, MIN_HEIGHT, monitor_width, monitor_height);
	mlx_set_window_pos(data.mlx, (monitor_width - data.width) / 2, (monitor_height - data.height) / 2);
	if (!data.mlx)
		return (1);
	data.image = mlx_new_image(data.mlx, data.width, data.height);
	if (!data.image)
		return (1);
	data.textures = malloc(sizeof(t_textures));
	if (!data.textures)
	{
		fprintf(stderr, "Error: Failed to allocate memory for textures\n");
		return (EXIT_FAILURE);
	}
	ft_memset(data.textures, 0, sizeof(t_textures));
	data.floor_color = 0xAAAABBCC; // Esimerkiksi sininen lattia
	data.ceiling_color = 0x00FFEEDD; // Esimerkiksi vaalean keltainen katto
	int status;
	status = parse_cubfile("test.cub", &data);
	/*
	if (load_textures(&data))
	{
		mlx_terminate(data.mlx);
		return (EXIT_FAILURE);
	}
	*/
	if (status)
	{
		mlx_terminate(data.mlx);
		return (EXIT_FAILURE);
	}
	if (is_wall(data.map.grid, data.player.x, data.player.y))
	{
		printf("Error: Player starts inside a wall\n");
		return (1);
	}
	mlx_image_to_window(data.mlx, data.image, 0, 0);
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	//free_textures(data.textures);
	free(data.textures);
	return (0);
}



