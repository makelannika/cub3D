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

void	rotate_right(t_cub3d *data)
{
	double	old_dir_x = data->ray_c.dir_x;
	data->ray_c.dir_x = data->ray_c.dir_x * cos(-data->mlx->delta_time * 3) - data->ray_c.dir_y * sin(-data->mlx->delta_time * 3);
	data->ray_c.dir_y = old_dir_x  * sin(-data->mlx->delta_time * 3) + data->ray_c.dir_y * cos(-data->mlx->delta_time * 3);
	double oldPlaneX = data->ray_c.plane_x;
	data->ray_c.plane_x = data->ray_c.plane_x * cos(-data->mlx->delta_time * 3) - data->ray_c.plane_y * sin(-data->mlx->delta_time * 3);
	data->ray_c.plane_y = oldPlaneX * sin(-data->mlx->delta_time * 3) + data->ray_c.plane_y * cos(-data->mlx->delta_time * 3);
	// data->map.p_angle -= 15;
	// if (data->map.p_angle < 0)
	// 	data->map.p_angle = 345;
	fov_cast(data, &data->ray_c, data->map.p_angle);
}

void	rotate_left(t_cub3d *data)
{
	double	old_dir_x = data->ray_c.dir_x;
	data->ray_c.dir_x = data->ray_c.dir_x * cos(data->mlx->delta_time * 3) - data->ray_c.dir_y * sin(data->mlx->delta_time * 3);
	data->ray_c.dir_y = old_dir_x  * sin(data->mlx->delta_time * 3) + data->ray_c.dir_y * cos(data->mlx->delta_time * 3);
	double oldPlaneX = data->ray_c.plane_x;
	data->ray_c.plane_x = data->ray_c.plane_x * cos(data->mlx->delta_time * 3) - data->ray_c.plane_y * sin(data->mlx->delta_time * 3);
	data->ray_c.plane_y = oldPlaneX * sin(data->mlx->delta_time * 3) + data->ray_c.plane_y * cos(data->mlx->delta_time * 3);
	// data->map.p_angle += 15;
	// if (data->map.p_angle > 360)
	// 	data->map.p_angle = 15;
	fov_cast(data, &data->ray_c, data->map.p_angle);
}
