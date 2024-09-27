/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:45:22 by amakela           #+#    #+#             */
/*   Updated: 2024/09/27 19:27:08 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	reset_minimap(t_cub3d * data)
{
	int	y;
	int	x;

	y = 0;
	while (y < 275)
	{
		x = 0;
		while (x < 275)
			mlx_put_pixel(data->minimap, x++, y, 255);
		y++;
	}
}

void	move_left(t_cub3d *data)
{
	if (data->map.offsetx < 3
		&& data->map.grid[data->map.player.y][data->map.player.x - 1] == '1')
		return ;
	data->map.offsetx -= 3;
	data->map.player.pix_x -= 3;
	if (data->map.offsetx < 0)
	{
		data->map.player.x -= 1;
		data->map.offsetx += 25;
	}
	reset_minimap(data);
	draw_minimap(data, data->map.player.y - 5, data->map.player.x -5);
	draw_player(data, data->map.p_angle);
}

void	move_right(t_cub3d *data)
{
	if (data->map.offsetx > 22
		&& data->map.grid[data->map.player.y][data->map.player.x + 1] == '1')
		return ;
	data->map.offsetx += 3;
	data->map.player.pix_x += 3;
	if (data->map.offsetx > 25)
	{
		data->map.player.x += 1;
		data->map.offsetx -= 25;
	}
	reset_minimap(data);
	draw_minimap(data, data->map.player.y - 5, data->map.player.x -5);
	draw_player(data, data->map.p_angle);
}

void	move_down(t_cub3d *data)
{
	if (data->map.offsety > 22
		&& data->map.grid[data->map.player.y + 1][data->map.player.x] == '1')
		return ;
	data->map.offsety += 3;
	data->map.player.pix_y += 3;
	if (data->map.offsety > 25)
	{
		data->map.player.y += 1;
		data->map.offsety -= 25;
	}
	reset_minimap(data);
	draw_minimap(data, data->map.player.y - 5, data->map.player.x -5);
	draw_player(data, data->map.p_angle);
}

void	move_up(t_cub3d *data)
{
	if (data->map.offsety < 3
		&& data->map.grid[data->map.player.y - 1][data->map.player.x] == '1')
		return ;
	data->map.offsety -= 3;
	data->map.player.pix_y -= 3;
	if (data->map.offsety < 0)
	{
		data->map.player.y -= 1;
		data->map.offsety += 25;
	}
	reset_minimap(data);
	draw_minimap(data, data->map.player.y - 5, data->map.player.x -5);
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
