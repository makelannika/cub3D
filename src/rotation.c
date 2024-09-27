/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:48:37 by amakela           #+#    #+#             */
/*   Updated: 2024/09/19 15:16:21 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rotate_right(t_cub3d *data)
{
	mlx_delete_image(data->mlx, data->minimap);
	data->minimap = mlx_texture_to_image(data->mlx, data->minimap_txtr);
	mlx_image_to_window(data->mlx, data->minimap, 0, 0);
	draw_minimap(data, data->map.player.y - 5, data->map.player.x -5);
	data->map.p_angle -= 15;
	if (data->map.p_angle < 0)
		data->map.p_angle = 345;
	draw_player(data, data->map.p_angle);
}

void	rotate_left(t_cub3d *data)
{
	mlx_delete_image(data->mlx, data->minimap);
	data->minimap = mlx_texture_to_image(data->mlx, data->minimap_txtr);
	mlx_image_to_window(data->mlx, data->minimap, 0, 0);
	draw_minimap(data, data->map.player.y - 5, data->map.player.x -5);
	data->map.p_angle += 15;
	if (data->map.p_angle > 360)
		data->map.p_angle = 15;
	draw_player(data, data->map.p_angle);
}

void	my_keyhook(mlx_key_data_t keydata, void *game_data)
{
	t_cub3d	*data;

	data = (t_cub3d *)game_data;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_right(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_left(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_up(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_left(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_right(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_down(data);
}
