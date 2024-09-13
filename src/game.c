/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:18:02 by linhnguy          #+#    #+#             */
/*   Updated: 2024/09/14 00:22:43 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	create_images(t_minimap *data)
{
	data->background_tex = mlx_load_png("assets/black_bg.png");
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	// data->arrow_tex = mlx_load_png("assets/player_icon.png");
	// data->arrow_png = mlx_texture_to_image(data->mlx, data->arrow_tex);
	// mlx_resize_image(data->arrow_png, 20, 20);
	// mlx_image_to_window(data->mlx, data->arrow_png, 625, 450);
	return (0);
}

int	init_game(t_minimap *data)
{
	data->mlx = mlx_init(1000, 900, "Cub3D", false);
	create_images(data);
	draw_player(data, data->p_angle);
	draw_minimap(data, data->player.y - 5, data->player.x -5);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}
