/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:48:37 by amakela           #+#    #+#             */
/*   Updated: 2024/10/25 11:58:45 by linhnguy         ###   ########.fr       */
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

double	normalize_vector(double *x, double *y)
{
	double	length;

	length = sqrt((*x) * (*x) + (*y) * (*y));
	if (length != 0 && length != 1.0)
	{
		*x /= length;
		*y /= length;
	}
	return (length);
}

void	rotate_left(t_cub3d *data, t_ray *ray_c)
{
	double	old_dir_x;
	double	old_plane_x;
	float	frame;

	frame = .06;
	old_dir_x = ray_c->dir_x;
	old_plane_x = ray_c->plane_x;
	ray_c->dir_x = ray_c->dir_x * cos(-frame) - ray_c->dir_y * sin(-frame);
	ray_c->dir_y = old_dir_x * sin(-frame) + ray_c->dir_y * cos(-frame);
	normalize_vector(&ray_c->dir_x, &ray_c->dir_y);
	ray_c->plane_x = ray_c->plane_x * cos(-frame) - ray_c->plane_y * sin(-frame);
	ray_c->plane_y = old_plane_x * sin(-frame) + ray_c->plane_y * cos(-frame);
	normalize_vector(&ray_c->plane_x, &ray_c->plane_y);
	ray_c->plane_x *= 0.66;
	ray_c->plane_y *= 0.66;
	fov_cast(data, ray_c);
}

void	rotate_right(t_cub3d *data, t_ray *ray_c)
{
	double	old_dir_x;
	double	old_plane_x;
	float	frame;

	frame = .06;
	old_dir_x = ray_c->dir_x;
	old_plane_x = ray_c->plane_x;
	ray_c->dir_x = ray_c->dir_x * cos(frame) - ray_c->dir_y * sin(frame);
	ray_c->dir_y = old_dir_x * sin(frame) + ray_c->dir_y * cos(frame);
	normalize_vector(&ray_c->dir_x, &ray_c->dir_y);
	ray_c->plane_x = ray_c->plane_x * cos(frame) - ray_c->plane_y * sin(frame);
	ray_c->plane_y = old_plane_x * sin(frame) + ray_c->plane_y * cos(frame);
	normalize_vector(&ray_c->plane_x, &ray_c->plane_y);
	ray_c->plane_x *= 0.66;
	ray_c->plane_y *= 0.66;
	fov_cast(data, ray_c);
}
