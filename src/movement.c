/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:45:22 by amakela           #+#    #+#             */
/*   Updated: 2024/09/14 00:23:10 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_left(t_minimap *data)
{
	mlx_delete_image(data->mlx, data->background_png);
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	data->offsetx = data->offsetx - 3;
	if (data->offsetx < 0)
	{
		data->player.x -= 1;
		data->offsetx += 25;
	}
	draw_minimap(data, data->player.y - 5, data->player.x -5);
	draw_player(data, data->p_angle);
}

void	move_right(t_minimap *data)
{
	mlx_delete_image(data->mlx, data->background_png);
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	data->offsetx = data->offsetx + 3;
	if (data->offsetx > 25)
	{
		data->player.x += 1;
		data->offsetx -= 25;
	}
	draw_minimap(data, data->player.y - 5, data->player.x -5);
	draw_player(data, data->p_angle);
}

void	move_down(t_minimap *data)
{
	mlx_delete_image(data->mlx, data->background_png);
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	data->offsety = data->offsety + 3;
	if (data->offsety > 25)
	{
		data->player.y += 1;
		data->offsety -= 25;
	}
	draw_minimap(data, data->player.y - 5, data->player.x -5);
	draw_player(data, data->p_angle);
}

void	move_up(t_minimap *data)
{
	mlx_delete_image(data->mlx, data->background_png);
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	data->offsety = data->offsety - 3;
	if (data->offsety < 25)
	{
		data->player.y -= 1;
		data->offsety += 25;
	}
	draw_minimap(data, data->player.y - 5, data->player.x -5);
	draw_player(data, data->p_angle);
}
