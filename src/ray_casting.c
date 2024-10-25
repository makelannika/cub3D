/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:17:24 by linhnguy          #+#    #+#             */
/*   Updated: 2024/10/25 19:38:22 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	get_wall_stats(t_ray *ray)
{
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
}

void	get_distance(t_cub3d *data, t_ray *ray)
{
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
}

void	shoot_ray(t_cub3d *data, t_ray *ray)
{
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
}

void	calc_step(t_ray *ray)
{
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
}

void	fov_cast(t_cub3d *data, t_ray *ray)
{
	draw_background(data);
	ray->side = 0;
	ray->screen_x = 0;
	while (ray->screen_x < SCREEN_WIDTH)
	{
		init_vars(ray);
		calc_step(ray);
		shoot_ray(data, ray);
		get_distance(data, ray);
		get_wall_stats(ray);
		draw_ray(data, ray, ray->screen_x);
		ray->screen_x++;
	}
}
