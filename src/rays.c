/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djelacik <djelacik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:29:26 by djelacik          #+#    #+#             */
/*   Updated: 2025/01/05 22:34:48 by djelacik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	draw_wall_column(mlx_image_t *image, int x, int start_y, int end_y, int color)
{
	int	y;

	y = start_y;
	while (y <= end_y)
	{
		if (y >= 0 && y < WIN_HEIGHT)
			mlx_put_pixel(image, x, y, color);
		y++;
	}
}

static double	normalize_angle(double angle)
{
	while (angle < -M_PI)
		angle += 2 * M_PI;
	while (angle > M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

// static double	calculate_corrected_distance(t_player player, double angle, char **map)
// {
// 	double	distance;
// 	double	corrected_distance;

// 	distance = calculate_distance(player, angle, map);
// 	corrected_distance = distance * cos(angle - player.angle);
// 	if (corrected_distance < 0.1)
// 		corrected_distance = 0.1;
// 	return (corrected_distance);
// }

static void	calculate_wall_limits(int *start_y, int *end_y, double corrected_distance)
{
	int wall_height;

	wall_height = (TILE_SIZE / corrected_distance) * 7;
	*start_y = (WIN_HEIGHT / 2) - (wall_height / 2);
	*end_y = (WIN_HEIGHT / 2) + (wall_height / 2);

	if (*start_y < 0)
		*start_y = 0;
	if (*end_y >= WIN_HEIGHT)
		*end_y = WIN_HEIGHT - 1;

	DBG_PRINT("Wall Height: %d, Start Y: %d, End Y: %d, Height Difference: %d\n", wall_height, *start_y, *end_y, *end_y - *start_y);
	DBG_PRINT("Wall Height: %d, Start Y: %d, End Y: %d\n", wall_height, *start_y, *end_y);
    DBG_PRINT("Height Change: %d\n", *end_y - *start_y); // Tämä tulostus
}

// void	draw_rays(t_data *data)
// {
// 	double	angle;
// 	int		screen_x;
// 	int		start_y;
// 	int		end_y;
// 	double	corrected_distance;

// 	angle = normalize_angle(data->player.angle - FOV / 2);
// 	screen_x = 0;
// 	while (screen_x < WIN_WIDTH)
// 	{
// 		corrected_distance = calculate_corrected_distance(data->player, angle, data->map);
// 		calculate_wall_limits(&start_y, &end_y, corrected_distance);
// 		draw_wall_column(data->image, screen_x, start_y, end_y, 0xFFFFFF);
// 		angle += FOV / WIN_WIDTH;
// 		screen_x++;
// 	}
// }

int calculate_hit_side(t_player player, double angle, char **map)
{
    double ray_dir_x;
    double ray_dir_y;
    double delta_dist_x;
    double delta_dist_y;
    double side_dist_x;
    double side_dist_y;
    int map_x;
    int map_y;
    int step_x;
    int step_y;
    int hit_side;

    // Säteen suunta (kulmasta)
    ray_dir_x = cos(angle);
    ray_dir_y = sin(angle);

    // Pelaajan grid-sijainti
    map_x = (int)player.x;
    map_y = (int)player.y;

    // Deltaetäisyydet
    delta_dist_x = fabs(1 / ray_dir_x);
    delta_dist_y = fabs(1 / ray_dir_y);

    // Lasketaan alkuetäisyydet
    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (player.x - map_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (map_x + 1.0 - player.x) * delta_dist_x;
    }
    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (player.y - map_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (map_y + 1.0 - player.y) * delta_dist_y;
    }

	DBG_PRINT("Ray Direction: (%f, %f), Delta Distances: (%f, %f)\n", ray_dir_x, ray_dir_y, delta_dist_x, delta_dist_y);
	DBG_PRINT("Step X: %d, Step Y: %d, Side Distances: (%f, %f), Map: (%d, %d)\n", step_x, step_y, side_dist_x, side_dist_y, map_x, map_y);
    // DDA: Eteneminen gridissä
    while (1)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            map_x += step_x;
            hit_side = 0; // Osuma x-seinään
        }
        else
        {
            side_dist_y += delta_dist_y;
            map_y += step_y;
            hit_side = 1; // Osuma y-seinään
        }
        if (map[map_y][map_x] == '1') // Osuma seinään
            break;
    }

    return hit_side;
}

t_ray	calculate_ray(t_data *data, double angle)
{
	t_ray ray;

	// Lasketaan säteen tiedot (distance, hit_x, hit_y, side jne.)
	ray.distance = calculate_distance(data->player, angle, data->map);
	ray.side = calculate_hit_side(data->player, angle, data->map);
	ray.wall_x = get_wall_x(ray.hit_x, ray.hit_y, ray.side);
	ray.texture = get_wall_texture(data, cos(angle), sin(angle), ray.side);

	DBG_PRINT("Ray Distance: %f, Wall X: %f, Side: %d\n", ray.distance, ray.wall_x, ray.side);
	return (ray);
}
double	calculate_corrected_distance(double distance, double ray_angle, double player_angle)
{
	double corrected_distance;

	corrected_distance = distance * cos(ray_angle - player_angle);

	// Debug-tuloste
	DBG_PRINT("Distance: %f, Ray Angle: %f, Player Angle: %f, Corrected Distance: %f\n", 
		distance, ray_angle, player_angle, corrected_distance);

	return (corrected_distance);
}

void	draw_single_ray(t_data *data, double angle, int screen_x)
{
	t_ray	ray;
	int		start_y;
	int		end_y;
	double	corrected_distance;

	ray = calculate_ray(data, angle);
	corrected_distance = calculate_corrected_distance(ray.distance, angle, data->player.angle);
	calculate_wall_limits(&start_y, &end_y, corrected_distance);

	DBG_PRINT("Screen X: %d, Corrected Distance: %f, Start Y: %d, End Y: %d\n", screen_x, corrected_distance, start_y, end_y);

	//draw_wall_column(data->image, screen_x, start_y, end_y, 0xFFFFFF);
	draw_wall_texture(data, &ray, screen_x, start_y, end_y);
}


// void	draw_rays(t_data *data)
// {
// 	double	angle;
// 	int		screen_x;

// 	// Alustetaan ensimmäisen säteen kulma
// 	angle = data->player.angle - FOV / 2;
// 	screen_x = 0;

// 	// Käy läpi kaikki näytön x-koordinaatit
// 	while (screen_x < WIN_WIDTH)
// 	{
// 		t_ray	ray;
// 		int		start_y;
// 		int		end_y;
// 		double	corrected_distance;

// 		// Laske säteen tiedot
// 		ray = calculate_ray(data, angle);

// 		// Korjaa etäisyys "fish-eye"-ilmiön välttämiseksi
// 		corrected_distance = calculate_corrected_distance(ray.distance, angle, data->player.angle);

// 		// Laske seinän ylä- ja alarajat
// 		calculate_wall_limits(&start_y, &end_y, corrected_distance);

// 		// Piirrä seinä tekstuurilla
// 		draw_wall_texture(data, &ray, screen_x, start_y, end_y);

// 		// Siirry seuraavaan säteeseen
// 		angle += FOV / (WIN_WIDTH);
// 		screen_x++;
// 	}
// }

void	draw_rays(t_data *data)
{
	double	angle;
	int		screen_x;

	// Alustetaan ensimmäisen säteen kulma
	angle = data->player.angle - FOV / 2;
	screen_x = 0;

	// Käy läpi kaikki näytön x-koordinaatit
	while (screen_x < WIN_WIDTH)
	{
		DBG_PRINT("Ray Angle: %f, Screen X: %d\n", angle, screen_x);
		// Käytä draw_single_ray-funktiota yhden säteen laskemiseen ja piirtämiseen
		draw_single_ray(data, angle, screen_x);

		// Siirry seuraavaan säteeseen
		angle += FOV / (WIN_WIDTH);
		screen_x++;
	}
}


void	draw_wall_texture(t_data *data, t_ray *ray, int screen_x, int start_y, int end_y)
{
	int		y;
	int		tex_x;
	int		tex_y;
	uint32_t	color;

	tex_x = (int)(ray->wall_x * ray->texture->width);
	tex_x = (int)(ray->wall_x * ray->texture->width);
	if ((ray->side == 0 && ray->dir_x > 0) || (ray->side == 1 && ray->dir_y < 0))
		tex_x = ray->texture->width - tex_x - 1;

	//DBG_PRINT("Wall X: %f, Tex X: %d, Ray Side: %d\n", ray->wall_x, tex_x, ray->side);
	//DBG_PRINT("Drawing Wall: Screen X: %d, Tex X: %d, Start Y: %d, End Y: %d\n", screen_x, tex_x, start_y, end_y);

	y = start_y;
	while (y <= end_y)
	{
		tex_y = (int)(((y - start_y) / (double)(end_y - start_y)) * ray->texture->height);
		color = get_texture_color(ray->texture, tex_x, tex_y);
		mlx_put_pixel(data->image, screen_x, y, color);
		y++;
	}
}

uint32_t	get_texture_color(mlx_texture_t *texture, int x, int y)
{
	return (*(uint32_t *)(texture->pixels + y * texture->width * 4 + x * 4));
}


double	get_wall_x(double hit_x, double hit_y, int hit_side)
{
	if (hit_side == 0)
		return (hit_y - floor(hit_y));
	else
		return (hit_x - floor(hit_x));
}

#include "../includes/cub3D.h"

mlx_texture_t *get_wall_texture(t_data *data, double dir_x, double dir_y, int side)
{
	if (side == 0) // X-seinä
	{
		if (dir_x > 0) // Itään
			return data->textures->east;
		else // Länteen
			return data->textures->west;
	}
	else // Y-seinä
	{
		if (dir_y > 0) // Etelään
			return data->textures->south;
		else // Pohjoiseen
			return data->textures->north;
	}
}