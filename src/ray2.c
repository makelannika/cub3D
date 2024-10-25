/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:17:24 by linhnguy          #+#    #+#             */
/*   Updated: 2024/10/24 22:21:38 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

double	degree_to_rad(float player_angle)
{
	double	rad;

	rad = player_angle * M_PI / 180.0;
	return (rad);
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

void	init_vars(t_ray *ray)
{
	ray->hit = 0;
	ray->camera_x = 2 * ray->screen_x / (double)SCREEN_WIDTH - 1;
	ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
	ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	fov_cast(t_cub3d *data, t_ray *ray)
{
	draw_background(data);
	ray->side = 0;
	ray->screen_x = 0;
	while (ray->screen_x < SCREEN_WIDTH)
	{
		init_vars(ray);
		if (ray->ray_dir_x < 0)
		{
			ray->step_x = -1;
			ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
		}
		else
		{
			ray->step_x = 1;
			ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
		}
		if (ray->ray_dir_y < 0)
		{
			ray->step_y = -1;
			ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
		}
		else
		{
			ray->step_y = 1;
			ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
		}
		while (!ray->hit)
		{
			if (ray->side_dist_x < ray->side_dist_y)
			{
				ray->side_dist_x += ray->delta_dist_x;
				ray->map_x += ray->step_x;
				ray->side = 0;
			}
			else
			{
				ray->side_dist_y += ray->delta_dist_y;
				ray->map_y += ray->step_y;
				ray->side = 1;
			}
			if (data->map.grid[ray->map_y][ray->map_x] == '1')
				ray->hit = 1;
		}
		if (ray->side == 0)
		{
			if (ray->map_x > ray->pos_x)
				data->wall_to_draw = (uint32_t *)data->west->pixels;
			else
				data->wall_to_draw = (uint32_t *)data->east->pixels;
			ray->distance = (ray->side_dist_x - ray->delta_dist_x);
		}
		else
		{
			if (ray->map_y > ray->pos_y)
				data->wall_to_draw = (uint32_t *)data->north->pixels;
			else
				data->wall_to_draw = (uint32_t *)data->south->pixels;
			ray->distance = (ray->side_dist_y - ray->delta_dist_y);
		}
		ray->wall_height = (int)(SCREEN_HEIGHT / ray->distance);
		ray->start = -ray->wall_height / 2 + SCREEN_HEIGHT / 2;
		ray->end = ray->wall_height / 2 + SCREEN_HEIGHT / 2;
		if (ray->side == 0)
			ray->wall_x = ray->pos_y + ray->distance * ray->ray_dir_y;
		else
			ray->wall_x = ray->pos_x + ray->distance * ray->ray_dir_x;
		ray->wall_x -= floor((ray->wall_x));
		ray->txtr_x = (int)(ray->wall_x * (double)(1000));
		if (ray->side == 0 && ray->ray_dir_x > 0)
			ray->txtr_x = 1000 - ray->txtr_x - 1;
		if (ray->side == 1 && ray->ray_dir_y < 0)
			ray->txtr_x = 1000 - ray->txtr_x - 1;
		draw_ray(data, ray, ray->screen_x);
		ray->screen_x++;
	}
}
