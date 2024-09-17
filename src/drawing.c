/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:59:12 by amakela           #+#    #+#             */
/*   Updated: 2024/09/12 18:06:17 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_square(t_minimap *data, float y_coor, float x_coor)
{
	int	x;
	int	y;
	int	xx;
	int	yy;

	y = 1;
	while (y < INDEX_HEIGHT)
	{
		yy = (int)(y_coor + y - data->offsety + 13);
		x = 1;
		while (x < INDEX_WIDTH)
		{
			xx = (int)(x_coor + x - data->offsetx + 13);
			if (xx < 0)
				xx = 0;
			if (xx > 0 && xx < 275 && yy > 0 && yy < 275)
				mlx_put_pixel(data->background_png, xx, yy, 0x0000FFFF);
			x++;
		}
		y++;
	}
}

int	draw_wall(t_minimap *data)
{
	int	y;
	int	x;
	int	x_reset;
	int	vertical = 0;
	int	horizontal = 0;

	y = data->player.y - 5;
	x = data->player.x - 5;
	x_reset = x;
	while (vertical < 12)
	{
		if (y >= data->map_height)
			break ;
		x = x_reset;
		horizontal = 0;
		while (horizontal < 12)
		{
			if ((y >= 0 && x >= 0) && !data->map[y][x])
				break ;
			if ((y >= 0 && x >= 0) && data->map[y][x] == '1')
				draw_square(data, vertical * INDEX_HEIGHT, horizontal * INDEX_WIDTH);
			x++;
			horizontal++;
		}
		y++;
		vertical++;
	}
	return (0);
}

void	draw_player(t_minimap *data, float angle)
{
	int	x;
	int	y;

	y = -2;
	while (y < 3)
	{
		x = -2;
		while (x < 3)
		{
			mlx_put_pixel(data->background_png, (int)PLAYER_X + x, (int)PLAYER_Y + y, 0xFFFFFF);
			x++;
		}
		y++;
	}
	fov_cast(data, angle);
	printf("## player pos: %i %i \n", data->player.x, data->player.y);
}
