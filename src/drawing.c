/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:59:12 by amakela           #+#    #+#             */
/*   Updated: 2024/10/25 19:32:41 by amakela          ###   ########.fr       */
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
				mlx_put_pixel(data->background, x++, y, data->ceiling);
			else
				mlx_put_pixel(data->background, x++, y, data->floor);
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

void	draw_pixel(t_cub3d *data, int x, int incr)
{
	int	pixel;

	pixel = reverse_bytes(data->wall_to_draw[incr]);
	mlx_put_pixel(data->background, x, data->ray.start, pixel);
}

void	draw_ray(t_cub3d *data, t_ray *ray, int screen_x)
{
	screen_x = 999 - screen_x;
	ray->txtr_x = 999 - ray->txtr_x;
	ray->increment = 1.0 * SCREEN_HEIGHT / ray->wall_height;
	ray->txtr_y = 0;
	while (ray->start <= ray->end)
	{
		if (ray->start >= 0 && ray->start < SCREEN_HEIGHT)
			draw_pixel(data, screen_x,
				(1000 * (int)(ray->txtr_y) + ray->txtr_x));
		ray->txtr_y += ray->increment;
		ray->start++;
	}
}
