/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:59:12 by amakela           #+#    #+#             */
/*   Updated: 2024/09/14 00:22:27 by amakela          ###   ########.fr       */
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

int	draw_minimap(t_minimap *data, int y, int x)
{
	int	minimap_y = 0;
	int	minimap_x = 0;

	while (minimap_y < 12)
	{
		if (y >= data->map_height)
			break ;
		x -= minimap_x;
		minimap_x = 0;
		while (minimap_x < 12)
		{
			if (y >= 0 && x >= (int)ft_strlen(data->map[y]))
				break ;
			if ((y >= 0 && x >= 0) && data->map[y][x] == '1')
				draw_square(data, minimap_y * INDEX_HEIGHT, minimap_x * INDEX_WIDTH);
			x++;
			minimap_x++;
		}
		y++;
		minimap_y++;
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
	ray_cast(data, angle);
}
