/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:18:02 by linhnguy          #+#    #+#             */
/*   Updated: 2024/10/25 20:06:38 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	validate_pngs(t_cub3d *data)
{
	if (data->north->width != 1000 || data->north->height != 1000
		|| data->south->width != 1000 || data->south->height != 1000
		|| data->west->width != 1000 || data->west->height != 1000
		|| data->east->width != 1000 || data->east->height != 1000)
		return (err("invalid png size", NULL));
	return (0);
}

int	init_background(t_cub3d *data)
{
	data->background = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->background)
		return (err("creating image failed", NULL));
	if (mlx_image_to_window(data->mlx, data->background, 0, 0) == -1)
		return (err("displaying image failed", NULL));
	return (0);
}

int	game(t_cub3d *data)
{
	data->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", false);
	if (!data->mlx)
		return (err("initializing mlx failed", NULL));
	if (init_background(data) || validate_pngs(data))
		return (1);
	init_casting(data);
	fov_cast(data, &data->ray);
	mlx_loop_hook(data->mlx, (void (*)(void *))my_keyhook, data);
	mlx_loop(data->mlx);
	return (0);
}
