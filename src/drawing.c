/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:59:12 by amakela           #+#    #+#             */
/*   Updated: 2024/09/27 20:15:40 by amakela          ###   ########.fr       */
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
		yy = y_coor + y - data->map.offsety + 13;
		x = 1;
		while (x < INDEX_WIDTH)
		{
			xx = x_coor + x - data->map.offsetx + 13;
			if (xx >= 0 && xx < 275 && yy >= 0 && yy < 275)
				mlx_put_pixel(data->background, xx, yy, 0x0000FFFF);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_cub3d *data, int y, int x)
{
	int	mini_y;
	int	mini_x;

	mini_y = 0;
	mini_x = 0;
	while (mini_y < 12)
	{
		if (y >= data->map.height)
			break ;
		x -= mini_x;
		mini_x = 0;
		while (mini_x < 12)
		{
			if (y >= 0 && x >= (int)ft_strlen(data->map.grid[y]))
				break ;
			if ((y >= 0 && x >= 0) && data->map.grid[y][x] == '1')
				draw_square(data, mini_y * INDEX_HEIGHT, mini_x * INDEX_WIDTH);
			x++;
			mini_x++;
		}
		y++;
		mini_y++;
	}
}

void	draw_player(t_cub3d *data)
{
	int	x;
	int	y;

	y = -1;
	while (y < 2)
	{
		x = -1;
		while (x < 2)
			mlx_put_pixel(data->background,
				PLAYER_X + x++, PLAYER_Y + y, 0xFFFFFF);
		y++;
	}
}

void	draw_background(t_cub3d *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < 1000)
	{
		x = 0;
		while (x < 1000)
		{
			if (y < 275 && x < 275)
				mlx_put_pixel(data->background, x++, y, 255);
			else if (y < 500)
				mlx_put_pixel(data->background, x++, y, data->ceiling);
			else
				mlx_put_pixel(data->background, x++, y, data->floor);
		}
		y++;
	}
}

void	draw_pixel(t_cub3d *data, int x, int incr)
{
	int	pixel;
	// printf("incr = %d\n", incr);
	pixel = reverse_bytes(data->wall_to_draw[incr]); /* with casting */
	// int	pixel = rgba_to_hex(data->wall_to_draw[incr * 4], /* without casting */
	// 					data->wall_to_draw[incr * 4 + 1],
	// 					data->wall_to_draw[incr * 4 + 2],
	// 					data->wall_to_draw[incr * 4 + 3]);
	// if (data->ray_c.start <= data->ray_c.end)
		mlx_put_pixel(data->background, x, data->ray_c.start, pixel);
}
