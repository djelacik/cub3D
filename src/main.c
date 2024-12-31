/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:02:56 by djelacik          #+#    #+#             */
/*   Updated: 2024/12/31 16:12:41 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

char	**init_map(void)
{
	char	**map;

	map = malloc(sizeof(char *) * 11);
	if (!map)
		return (NULL);
	map[0] = "1111111111";
	map[1] = "1000000001";
	map[2] = "1001111001";
	map[3] = "1001001001";
	map[4] = "1001001001";
	map[5] = "1000000001";
	map[6] = "1001111101";
	map[7] = "1000000001";
	map[8] = "1111111111";
	map[9] = NULL;
	return (map);
}


int	is_wall(char **map, double x, double y)
{
	if (map[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

void	draw_square(mlx_image_t *image, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			// Piirrä viivat neliön reunoille
			if (i == 0 || i == TILE_SIZE - 1 || j == 0 || j == TILE_SIZE - 1)
				mlx_put_pixel(image, x + i, y + j, 0xFF0000); // Punainen viiva
			else
				mlx_put_pixel(image, x + i, y + j, color); // Täyttö
			j++;
		}
		i++;
	}
}


void	draw_map(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == '1')
				draw_square(data->image, x * TILE_SIZE,
					y * TILE_SIZE, 0xFFFFFF); // Valkoinen täyttö
			else
				draw_square(data->image, x * TILE_SIZE,
					y * TILE_SIZE, 0xAAAAAA); // Harmaa lattia
			x++;
		}
		y++;
	}
}

void	draw_player(t_data *data)
{
	int	x;
	int	y;
	int	i;
	int	j;
	int	size;

	x = (int)(data->player.x * TILE_SIZE);
	y = (int)(data->player.y * TILE_SIZE);
	size = 5;
	i = -size / 2;
	while (i <= size / 2)
	{
		j = -size / 2;
		while (j <= size / 2)
		{
			if (x + i >= 0 && x + i < WIN_WIDTH &&
				y + j >= 0 && y + j < WIN_HEIGHT)
			{
				mlx_put_pixel(data->image, x + i, y + j, 0x00FFFF);
			}
			j++;
		}
		i++;
	}
}


void	draw_rays(t_data *data)
{
	double	ray_x;
	double	ray_y;
	double	angle;
	int		screen_x;
	int		screen_y;

	angle = data->player.angle - FOV / 2;
	while (angle <= data->player.angle + FOV / 2)
	{
		ray_x = data->player.x;
		ray_y = data->player.y;
		while (data->map[(int)ray_y][(int)ray_x] != '1')
		{
			ray_x += cos(angle) * STEP_SIZE;
			ray_y += sin(angle) * STEP_SIZE;
			screen_x = ray_x * TILE_SIZE;
			screen_y = ray_y * TILE_SIZE;
			printf("Ray angle: %f, Hit: x = %f, y = %f, Screen: x = %d, y = %d\n",
			angle, ray_x, ray_y, screen_x, screen_y);
			if (screen_x >= 0 && screen_x < WIN_WIDTH
				&& screen_y >= 0 && screen_y < WIN_HEIGHT)
				mlx_put_pixel(data->image, screen_x, screen_y, 0xFF00FF);
		}
		angle += 0.01;
	}
}

void	render(t_data *data)
{
	// Poista edellinen kuva ja luo uusi
	mlx_delete_image(data->mlx, data->image);
	data->image = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx_image_to_window(data->mlx, data->image, 0, 0);
	//printf("Player position: x = %f, y = %f, angle = %f\n",
	//	data->player.x, data->player.y, data->player.angle);
	draw_map(data);
	draw_player(data);
	draw_rays(data);
}

int	main(void)
{
	t_data	data;

	data.map = init_map();
	if (!data.map)
		return (1);
	data.player.x = 2;
	data.player.y = 2;
	data.player.angle = 0.0;
	data.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Cub3D Ray-Casting", false);
	if (!data.mlx)
		return (1);
	data.image = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data.image)
		return (1);
	mlx_image_to_window(data.mlx, data.image, 0, 0);
	mlx_key_hook(data.mlx, handle_keys, &data);
	mlx_loop_hook(data.mlx, (void (*)(void *))render, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	return (0);
}
