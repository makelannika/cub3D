/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:18:02 by linhnguy          #+#    #+#             */
/*   Updated: 2024/09/19 13:27:16 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	create_images(t_minimap *data)
{
	data->background_tex = mlx_load_png("assets/black_bg.png");
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	return (0);
}

int	init_game(t_cub3d *data)
{
	data->map.mlx = mlx_init(1000, 900, "Cub3D", false);
	create_images(&data->map);
	draw_player(&data->map, data->map.p_angle);
	draw_minimap(&data->map, data->map.player.y - 5, data->map.player.x -5);
	mlx_key_hook(data->map.mlx, &my_keyhook, &data->map);
	mlx_loop(data->map.mlx);
	mlx_terminate(data->map.mlx);
	return (0);
}
