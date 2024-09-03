/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:18:02 by linhnguy          #+#    #+#             */
/*   Updated: 2024/09/03 20:39:57 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int create_images(t_minimap *data)
{
	data->background_tex = mlx_load_png("assets/minimap_background.png");
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_resize_image(data->background_png, 400, 400);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	data->arrow_tex = mlx_load_png("assets/player_icon.png");
	data->arrow_png = mlx_texture_to_image(data->mlx, data->arrow_tex);
	mlx_resize_image(data->arrow_png, 40, 40);
	mlx_image_to_window(data->mlx, data->arrow_png, 25, 25);
	return (0);
}

int init_game(t_minimap *data)
{
	data->mlx = mlx_init(1600, 1600, "Cub3D", false);
	create_images(data);
	mlx_loop(data->mlx);
	return (0);
}

int main()
{
	t_minimap	data;
	data = (t_minimap){0};
	init_game(&data);
}

// void	my_keyhook(mlx_key_data_t keydata, void *game_data)
// {
// 	t_data			*data;

// 	data = (t_data *)game_data;
// 	if (data->is_end == true)
// 		return ;
// 	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
// 		mlx_close_window(data->mlx);
// 	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
// 		move_up(data);
// 	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
// 		move_left(data);
// 	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
// 		move_right(data);
// 	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
// 		move_down(data);
// }