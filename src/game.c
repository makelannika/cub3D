/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:18:02 by linhnguy          #+#    #+#             */
/*   Updated: 2024/09/22 21:02:30 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	create_images(t_cub3d *data)
{
	data->minimap_txtr = mlx_load_png("assets/black_bg.png");
	if (mlx_errno)
		return (err("loading png failed", NULL));
	data->minimap = mlx_texture_to_image(data->mlx, data->minimap_txtr);
	data->no = mlx_texture_to_image(data->mlx, data->no_txtr);
	data->so = mlx_texture_to_image(data->mlx, data->so_txtr);
	data->we = mlx_texture_to_image(data->mlx, data->we_txtr);
	data->ea = mlx_texture_to_image(data->mlx, data->ea_txtr);
	if (mlx_errno)
		return (err("creating images failed", NULL));
	mlx_image_to_window(data->mlx, data->minimap, 0, 0);
	if (mlx_errno)
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
