/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:59:12 by amakela           #+#    #+#             */
/*   Updated: 2024/11/05 15:07:21 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
			if (y < 500)
				mlx_put_pixel(data->background, x++, y, data->ceiling[1]);
			else
				mlx_put_pixel(data->background, x++, y, data->floor[1]);
		}
		y++;
	}
}

int	reverse_bytes(int p)
{
	return (((p & 0xFF) << 24)
		| ((p & 0xFF00) << 8)
		| ((p & 0xFF0000) >> 8)
		| ((p & 0xFF000000) >> 24));
}

void	draw_pixel(t_cub3d *data, t_draw *draw, int x, int incr)
{
	int	pixel;

	pixel = reverse_bytes(draw->wall_to_draw[incr]);
	mlx_put_pixel(data->background, x, draw->start, pixel);
}

void	draw_ray(t_cub3d *data, t_draw *draw, int screen_x)
{
	screen_x = 999 - screen_x;
	draw->txtr_x = 999 - draw->txtr_x;
	draw->increment = 1.0 * SCREEN_HEIGHT / draw->wall_height;
	draw->txtr_y = 0;
	while (draw->start < draw->end)
	{
		if (draw->start >= 0 && draw->start < SCREEN_HEIGHT)
			draw_pixel(data, &data->draw, screen_x,
				(1000 * (int)(draw->txtr_y) + draw->txtr_x));
		draw->txtr_y += draw->increment;
		draw->start++;
	}
}
