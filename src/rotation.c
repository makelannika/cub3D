/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:48:37 by amakela           #+#    #+#             */
/*   Updated: 2024/10/25 20:08:26 by amakela          ###   ########.fr       */
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

void	rotate_left(t_cub3d *data, t_ray *ray)
{
	double	old_dir_x;
	double	old_plane_x;
	float	frame;

	frame = .06;
	old_dir_x = ray->dir_x;
	old_plane_x = ray->plane_x;
	ray->dir_x = ray->dir_x * cos(-frame) - ray->dir_y * sin(-frame);
	ray->dir_y = old_dir_x * sin(-frame) + ray->dir_y * cos(-frame);
	normalize_vector(&ray->dir_x, &ray->dir_y);
	ray->plane_x = ray->plane_x * cos(-frame) - ray->plane_y * sin(-frame);
	ray->plane_y = old_plane_x * sin(-frame) + ray->plane_y * cos(-frame);
	normalize_vector(&ray->plane_x, &ray->plane_y);
	ray->plane_x *= 0.66;
	ray->plane_y *= 0.66;
	fov_cast(data, ray);
}

void	rotate_right(t_cub3d *data, t_ray *ray)
{
	double	old_dir_x;
	double	old_plane_x;
	float	frame;

	frame = .06;
	old_dir_x = ray->dir_x;
	old_plane_x = ray->plane_x;
	ray->dir_x = ray->dir_x * cos(frame) - ray->dir_y * sin(frame);
	ray->dir_y = old_dir_x * sin(frame) + ray->dir_y * cos(frame);
	normalize_vector(&ray->dir_x, &ray->dir_y);
	ray->plane_x = ray->plane_x * cos(frame) - ray->plane_y * sin(frame);
	ray->plane_y = old_plane_x * sin(frame) + ray->plane_y * cos(frame);
	normalize_vector(&ray->plane_x, &ray->plane_y);
	ray->plane_x *= 0.66;
	ray->plane_y *= 0.66;
	fov_cast(data, ray);
}
