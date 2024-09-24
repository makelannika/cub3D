/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:19:25 by amakela           #+#    #+#             */
/*   Updated: 2024/09/24 15:12:12 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	is_equal(double a, double b)
{
	return (fabs(a - b) < 1e-9);
}

void	horizontal_hit(t_map map, t_ray *ray_c)
{
	ray_c->ray_distance = (ray_c->side_dist_y - ray_c->delta_dist_y) * 25;
	if (map.player.y > ray_c->ray_index_y)
	// {
	//     printf("north\n");
		ray_c->wall_hit_y = (ray_c->ray_index_y + 1) * 25;
	// }
	else
	// {
	//     printf("south\n");
		ray_c->wall_hit_y = ray_c->ray_index_y * 25;
	// }
	ray_c->wall_hit_x = (ray_c->unit_x + (ray_c->side_dist_y - ray_c->delta_dist_y) * ray_c->ray_dir_x) * 25;
}

void	vertical_hit(t_map map, t_ray *ray_c)
{
	ray_c->ray_distance = (ray_c->side_dist_x - ray_c->delta_dist_x) * 25;
	if (map.player.x > ray_c->ray_index_x)
	// {
	//     printf("west\n");
		ray_c->wall_hit_x = (ray_c->ray_index_x + 1) * 25;
	// }
	else
	// {
	//     printf("east\n");
		ray_c->wall_hit_x = ray_c->ray_index_x * 25;
	// }
	ray_c->wall_hit_y = (ray_c->unit_y + (ray_c->side_dist_x - ray_c->delta_dist_x) * ray_c->ray_dir_y) * 25;
}

void	forward(t_ray *ray_c, char coor)
{
	if (coor == 'x')
	{
		ray_c->side_dist_x += ray_c->delta_dist_x;
		ray_c->ray_index_x += ray_c->step_x;
		ray_c->side = 0;
	}
	else if (coor == 'y')
	{
		ray_c->side_dist_y += ray_c->delta_dist_y;
		ray_c->ray_index_y -= ray_c->step_y;
		ray_c->side = 1;
	}
}

void	step_pos(t_ray *ray_c, char coor)
{
	if (coor == 'x')
	{
		ray_c->step_x = 1;
		ray_c->side_dist_x = (ray_c->ray_index_x + 1.0 - ray_c->unit_x) * ray_c->delta_dist_x;
	}
	else if (coor == 'y')
	{
		ray_c->step_y = 1;
		ray_c->side_dist_y = (ray_c->unit_y - ray_c->ray_index_y) * ray_c->delta_dist_y;
	}
}

void	step_neg(t_ray *ray_c, char coor)
{
	if (coor == 'x')
	{
		ray_c->step_x = -1;
		ray_c->side_dist_x = (ray_c->unit_x - ray_c->ray_index_x) * ray_c->delta_dist_x;
	}
	else if (coor == 'y')
	{
		ray_c->step_y = -1;
		ray_c->side_dist_y = (ray_c->ray_index_y + 1.0 - ray_c->unit_y) * ray_c->delta_dist_y;
	}
}

void	set_side_dist(t_ray *ray_c)
{
	if (is_equal(ray_c->ray_dir_x, 0.0))
		ray_c->side_dist_x = DBL_MAX;
	else if (ray_c->ray_dir_x < 0.0)
		step_neg(ray_c, 'x');
	else
	{
		step_pos(ray_c, 'x');
	}
	if (is_equal(ray_c->ray_dir_y, 0.0))
		ray_c->side_dist_y = DBL_MAX;
	else if (ray_c->ray_dir_y < 0.0)
		step_neg(ray_c, 'y');
	else
		step_pos(ray_c, 'y');
}

void	init_vars(t_map map, t_ray *ray_c)
{
	ray_c->delta_dist_x = fabs(1 / ray_c->ray_dir_x);
	ray_c->delta_dist_y = fabs(1 / ray_c->ray_dir_y);
	ray_c->unit_x = map.player.pix_x / 25;
	ray_c->unit_y = map.player.pix_y / 25;
	ray_c->ray_index_x = map.player.x;
	ray_c->ray_index_y = map.player.y;
	ray_c->hit = 0;
	ray_c->side = 0;
}

void	ray_cast(t_cub3d *data, t_ray *ray_c)
{
	init_vars(data->map, ray_c);
	set_side_dist(ray_c);
	while (!ray_c->hit)
	{
		if (ray_c->side_dist_x < ray_c->side_dist_y)
			forward(ray_c, 'x');
		else
			forward(ray_c, 'y');
		if (data->map.grid[ray_c->ray_index_y][ray_c->ray_index_x] == '1')
			ray_c->hit = 1;
	}
	if (!ray_c->side)
		vertical_hit(data->map, ray_c);
	else
		horizontal_hit(data->map, ray_c);
}

void	fov_cast(t_cub3d *data, t_ray *ray_c, float player_angle)
{
	double	rad;
	float	ray;
	int		x;
	int		y;
	int		i;

	ray = 0;
	while (ray < 60)
	{
		ray_c->current_angle = player_angle - 30 + ray;
		rad = ray_c->current_angle * M_PI / 180.0;
		ray_c->ray_dir_x = cos(rad);
		ray_c->ray_dir_y = sin(rad);
		ray_cast(data, ray_c);
		i = 0;
		while (i < ray_c->ray_distance)
		{
			x = PLAYER_X + (int)(ray_c->ray_dir_x * i);
			y = PLAYER_Y - (int)(ray_c->ray_dir_y * i);
			if (x > 0 && x < 275 && y > 0 && y < 275)
				mlx_put_pixel(data->minimap, x, y, 0xFFFFFF);
			i++;
		}
		ray += .06;
	}
}
