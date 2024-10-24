/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:48:37 by amakela           #+#    #+#             */
/*   Updated: 2024/09/27 19:35:01 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	reset_minimap(t_cub3d *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < 275)
	{
		x = 0;
		while (x < 275)
			mlx_put_pixel(data->background, x++, y, 255);
		y++;
	}
}

double normalize_vector(double *x, double *y)
{
    double length = sqrt((*x) * (*x) + (*y) * (*y));
    if (length != 0 && length != 1.0)
    {
        *x /= length;
        *y /= length;
    }
    return length;
}

void	rotate_left(t_cub3d *data)
{
	double	old_dir_x = data->ray_c.dir_x;
	data->ray_c.dir_x = data->ray_c.dir_x * cos(-data->mlx->delta_time * 3) - data->ray_c.dir_y * sin(-data->mlx->delta_time * 3);
	data->ray_c.dir_y = old_dir_x  * sin(-data->mlx->delta_time * 3) + data->ray_c.dir_y * cos(-data->mlx->delta_time * 3);
	normalize_vector(&data->ray_c.dir_x, &data->ray_c.dir_y);
	double oldPlaneX = data->ray_c.plane_x;
	data->ray_c.plane_x = data->ray_c.plane_x * cos(-data->mlx->delta_time * 3) - data->ray_c.plane_y * sin(-data->mlx->delta_time * 3);
	data->ray_c.plane_y = oldPlaneX * sin(-data->mlx->delta_time * 3) + data->ray_c.plane_y * cos(-data->mlx->delta_time * 3);
	normalize_vector(&data->ray_c.plane_x, &data->ray_c.plane_y);
    data->ray_c.plane_x *= 0.66;
    data->ray_c.plane_y *= 0.66;
	fov_cast(data, &data->ray_c);
}

void	rotate_right(t_cub3d *data)
{
	double	old_dir_x = data->ray_c.dir_x;
	data->ray_c.dir_x = data->ray_c.dir_x * cos(data->mlx->delta_time * 3) - data->ray_c.dir_y * sin(data->mlx->delta_time * 3);
	data->ray_c.dir_y = old_dir_x  * sin(data->mlx->delta_time * 3) + data->ray_c.dir_y * cos(data->mlx->delta_time * 3);
	normalize_vector(&data->ray_c.dir_x, &data->ray_c.dir_y);
	double oldPlaneX = data->ray_c.plane_x;
	data->ray_c.plane_x = data->ray_c.plane_x * cos(data->mlx->delta_time * 3) - data->ray_c.plane_y * sin(data->mlx->delta_time * 3);
	data->ray_c.plane_y = oldPlaneX * sin(data->mlx->delta_time * 3) + data->ray_c.plane_y * cos(data->mlx->delta_time * 3);
	normalize_vector(&data->ray_c.plane_x, &data->ray_c.plane_y);
    data->ray_c.plane_x *= 0.66;
    data->ray_c.plane_y *= 0.66;
	fov_cast(data, &data->ray_c);
}
