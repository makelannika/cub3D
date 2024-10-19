/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:18:02 by linhnguy          #+#    #+#             */
/*   Updated: 2024/09/27 19:43:40 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_png_sizes(t_cub3d *data)
{
	if (data->north->width != 1000 || data->north->height != 1000
		|| data->south->width != 1000 || data->south->height != 1000
		|| data->west->width != 1000 || data->west->height != 1000
		|| data->east->width != 1000 || data->east->height != 1000)
		return (1);
	return (0);
}

int	create_images(t_cub3d *data)
{
	if (check_png_sizes(data))
		return (err("invalid png size", NULL));
	data->background = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->background)
		return (err("creating image failed", NULL));
	if (mlx_image_to_window(data->mlx, data->background, 0, 0) == -1)
		return (err("displaying image failed", NULL));
	return (0);
}

int	init_game(t_cub3d *data)
{
	data->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", false);
	if (!data->mlx)
		return (err("initializing mlx failed", NULL));
	if (create_images(data))
		return (1);
	data->ray_c.pos_x = data->map.player.x + .5;
	data->ray_c.pos_y = data->map.player.y + .5;
	float	rad = degree_to_rad(data->map.p_angle);
	data->ray_c.dir_x = cos(rad);
	data->ray_c.dir_y = sin(rad);
	fov_cast(data, &data->ray_c);
	// mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop_hook(data->mlx, (void (*)(void *))my_keyhook, data);
	mlx_loop(data->mlx);
	return (0);
}
