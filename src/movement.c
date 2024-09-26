/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:45:22 by amakela           #+#    #+#             */
/*   Updated: 2024/09/26 21:36:05 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_left(t_cub3d *data)
{
	if (data->map.offsetx < 3
		&& data->map.grid[data->map.player.y][data->map.player.x - 1] == '1')
		return ;
	mlx_delete_image(data->mlx, data->minimap);
	data->minimap = mlx_texture_to_image(data->mlx, data->minimap_txtr);
	mlx_image_to_window(data->mlx, data->minimap, 0, 0);
	data->map.offsetx -= 3;
	data->map.player.pix_x -= 3;
	if (data->map.offsetx < 0)
	{
		data->map.player.x -= 1;
		data->map.offsetx += 25;
	}
	draw_minimap(data, data->map.player.y - 5, data->map.player.x -5);
	draw_player(data, data->map.p_angle);
}

void	move_right(t_cub3d *data)
{
	if (data->map.offsetx > 22
		&& data->map.grid[data->map.player.y][data->map.player.x + 1] == '1')
		return ;
	mlx_delete_image(data->mlx, data->minimap);
	data->minimap = mlx_texture_to_image(data->mlx, data->minimap_txtr);
	mlx_image_to_window(data->mlx, data->minimap, 0, 0);
	data->map.offsetx += 3;
	data->map.player.pix_x += 3;
	if (data->map.offsetx > 25)
	{
		data->map.player.x += 1;
		data->map.offsetx -= 25;
	}
	draw_minimap(data, data->map.player.y - 5, data->map.player.x -5);
	draw_player(data, data->map.p_angle);
}

void	move_down(t_cub3d *data)
{
	if (data->map.offsety > 22
		&& data->map.grid[data->map.player.y + 1][data->map.player.x] == '1')
		return ;
	mlx_delete_image(data->mlx, data->minimap);
	data->minimap = mlx_texture_to_image(data->mlx, data->minimap_txtr);
	mlx_image_to_window(data->mlx, data->minimap, 0, 0);
	data->map.offsety += 3;
	data->map.player.pix_y += 3;
	if (data->map.offsety > 25)
	{
		data->map.player.y += 1;
		data->map.offsety -= 25;
	}
	draw_minimap(data, data->map.player.y - 5, data->map.player.x -5);
	draw_player(data, data->map.p_angle);
}

void	move_up(t_cub3d *data)
{
	if (data->map.offsety < 3
		&& data->map.grid[data->map.player.y - 1][data->map.player.x] == '1')
		return ;
	mlx_delete_image(data->mlx, data->minimap);
	data->minimap = mlx_texture_to_image(data->mlx, data->minimap_txtr);
	mlx_image_to_window(data->mlx, data->minimap, 0, 0);
	data->map.offsety -= 3;
	data->map.player.pix_y -= 3;
	if (data->map.offsety < 0)
	{
		data->map.player.y -= 1;
		data->map.offsety += 25;
	}
	draw_minimap(data, data->map.player.y - 5, data->map.player.x -5);
	draw_player(data, data->map.p_angle);
}
