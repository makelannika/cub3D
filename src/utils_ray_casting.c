/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ray_casting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:37:14 by amakela           #+#    #+#             */
/*   Updated: 2024/10/26 15:26:52 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_casting(t_map *map, t_ray *ray)
{
	ray->hit = 0;
	ray->camera_x = 2 * ray->screen_x / (double)SCREEN_WIDTH - 1;
	ray->ray_dir_x = ray->dir_x + ray->plane_x * ray->camera_x;
	ray->ray_dir_y = ray->dir_y + ray->plane_y * ray->camera_x;
	map->x = (int)ray->pos_x;
	map->y = (int)ray->pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

double	degree_to_rad(float player_angle)
{
	double	rad;

	rad = player_angle * M_PI / 180.0;
	return (rad);
}

void	init_player(t_cub3d *data)
{
	float	rad;

	rad = degree_to_rad(data->map.angle);
	data->ray.pos_x = data->map.x + .5;
	data->ray.pos_y = data->map.y + .5;
	data->ray.dir_x = cos(rad);
	data->ray.dir_y = sin(rad);
}
