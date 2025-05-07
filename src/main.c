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

static bool	init_mlx_data(t_data *data)
{
	int	mw;
	int mh;

	data->mlx = mlx_init(MIN_WIDTH, MIN_HEIGHT, "Cub3D Ray-Casting", true);
	if (!data->mlx)
	{
		data->error_msg = "Failed to initialize MLX";
		return (false);
	}
	data->textures = gc_alloc(sizeof(t_textures));
	if (!data->textures)
	{
		mlx_terminate(data->mlx);
		data->error_msg = "Failed to allocate memory for textures";
		return (false);
	}
	ft_memset(data->textures, 0, sizeof(t_textures));
	mlx_get_monitor_size(0, &mw, &mh);
	data->width = mw / 2;
	data->height = mh / 2;
	mlx_set_window_size(data->mlx, data->width, data->height);
	mlx_set_window_limit(data->mlx, MIN_WIDTH, MIN_HEIGHT, mw, mh);
	mlx_set_window_pos(data->mlx, (mw - data->width) / 2, (mh - data->height) / 2);
	return (true);
}

bool	initializer(t_data *data, char *filename, bool strict)
{
	int	status;

	status = 0;
	ft_memset(data, 0, sizeof(t_data));
	data->strict = strict;
	data->player.speed = 0.025;
	if (!init_mlx_data(data))
		return (EXIT_FAILURE);
	status = parse_cubfile(filename, data);
	if (status)
	{
		mlx_terminate(data->mlx);
		if (data->textures)
			free_textures(data->textures);
		return (EXIT_FAILURE);
	}
	data->camera.x = data->width / 2;
	data->camera.y = data->height / 2;
	data->image = mlx_new_image(data->mlx, data->width, data->height);
	if (!data->image)
	{
		mlx_terminate(data->mlx);
		free_textures(data->textures);
		data->error_msg = "Failed to create image";
		return (EXIT_FAILURE);
	}
	if (!load_hud_textures(data))
	{
		mlx_terminate(data->mlx);
		free_textures(data->textures);
		data->error_msg = "Failed to load hud textures";
		return (EXIT_FAILURE);
	}
	if (is_wall(data, data->player.x, data->player.y))
	{
		mlx_terminate(data->mlx);
		free_textures(data->textures);
		free_hud_textures(data);
		data->error_msg = "Player starts inside a wall";
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

bool	has_cub_extension(char *filename)
{
	int len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	return (ft_strncmp(filename + len - 4, ".cub", 4) == 0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		error;
	bool	strict;
	
	strict = false;
	if (argc < 2 || !has_cub_extension(argv[1]) || argc > 3 || (argc == 3 && ft_strncmp(argv[2], "--strict", 9) != 0))
	{
		printf("Usage: %s <.cub file> [--strict]\n", argv[0]);
		return (EXIT_FAILURE);
	}
	if (argc == 3)
		strict = true;
	error = initializer(&data, argv[1], strict);
	if (error)
		error_exit(data.error_msg);
	mlx_image_to_window(data.mlx, data.image, 0, 0);
	mlx_loop_hook(data.mlx, loop_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	free_textures(data.textures);
	free_hud_textures(&data);
	//gc_free(data.textures);
	gc_free_all();
	return (EXIT_SUCCESS);
}
