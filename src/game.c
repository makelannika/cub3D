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
	data->minimap_txtr = mlx_load_png("assets/minimap.png");
	if (!data->minimap_txtr)
		return (err("loading png failed", NULL));
	data->minimap = mlx_texture_to_image(data->mlx, data->minimap_txtr);
	data->background = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->minimap || !data->background)
		return (err("creating image failed", NULL));
	if (mlx_image_to_window(data->mlx, data->background, 0, 0) == -1
	|| mlx_image_to_window(data->mlx, data->minimap, 0, 0) == -1)
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
	draw_player(data, data->map.p_angle);
	draw_minimap(data, data->map.player.y - 5, data->map.player.x -5);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	return (0);
}
