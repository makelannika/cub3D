/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:59:12 by amakela           #+#    #+#             */
/*   Updated: 2024/09/19 18:50:44 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	draw_square(t_cub3d *data, int y_coor, int x_coor)
{
	int	x;
	int	y;
	int	xx;
	int	yy;

	y = 1;
	while (y < INDEX_HEIGHT)
	{
		yy = (int)(y_coor + y - data->map.offsety + 13);
		x = 1;
		while (x < INDEX_WIDTH)
		{
			xx = (int)(x_coor + x - data->map.offsetx + 13);
			if (xx < 0)
				xx = 0;
			if (xx > 0 && xx < 275 && yy > 0 && yy < 275)
				mlx_put_pixel(data->minimap, xx, yy, 0x0000FFFF);
			x++;
		}
		y++;
	}
}

int	draw_minimap(t_cub3d *data, int y, int x)
{
	int	minimap_y = 0;
	int	minimap_x = 0;

	while (minimap_y < 12)
	{
		if (y >= data->map.height)
			break ;
		x -= minimap_x;
		minimap_x = 0;
		while (minimap_x < 12)
		{
			if (y >= 0 && x >= (int)ft_strlen(data->map.grid[y]))
				break ;
			if ((y >= 0 && x >= 0) && data->map.grid[y][x] == '1')
				draw_square(data, minimap_y * INDEX_HEIGHT, minimap_x * INDEX_WIDTH);
			x++;
			minimap_x++;
		}
		y++;
		minimap_y++;
	}
	return (0);
}

void	draw_player(t_cub3d *data, float angle)
{
	int	x;
	int	y;

	y = -1;
	while (y < 2)
	{
		x = -1;
		while (x < 2)
			mlx_put_pixel(data->minimap, PLAYER_X + x++, PLAYER_Y + y, 0xFFFFFF);
		y++;
	}
	fov_cast(data, angle);
}
