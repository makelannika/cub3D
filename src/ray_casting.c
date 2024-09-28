/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:01:45 by amakela           #+#    #+#             */
/*   Updated: 2024/09/27 20:16:12 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	is_equal(double a, double b)
{
	return (fabs(a - b) < 1e-9);
}

void	horizontal_hit(t_map map, t_ray *ray_c, t_cub3d *data)
{
	// printf("player y is %i ray y is %i\n", map.player.y, ray_c->ray_index_y);
	// printf("##side dist y is %f delta dist y %f\n", ray_c->side_dist_y , ray_c->delta_dist_y);
	ray_c->ray_distance = (ray_c->side_dist_y - ray_c->delta_dist_y) * 25;
	if (map.player.y > ray_c->ray_index_y)
	{
		// printf("player y is %i ray index y is %i\n", map.player.y, ray_c->ray_index_y);
	    // printf("north\n");
		ray_c->wall_hit_y = (ray_c->ray_index_y + 1) * 25;
		data->wall_to_draw = (uint32_t *)data->south->pixels;
		// data->wall_to_draw = data->north->pixels;
	}
	else
	{
	    // printf("south\n");
		ray_c->wall_hit_y = ray_c->ray_index_y * 25;
		data->wall_to_draw = (uint32_t *)data->north->pixels;
		// data->wall_to_draw = data->south->pixels;
	}
	ray_c->wall_hit_x = (ray_c->unit_x + (ray_c->side_dist_y - ray_c->delta_dist_y) * ray_c->ray_dir_x) * 25;
}

void	vertical_hit(t_map map, t_ray *ray_c, t_cub3d *data)
{
	// printf("player x is %i ray x is %i\n", map.player.x, ray_c->ray_index_x);
	// printf("##side dist x is %f delta dist x %f\n", ray_c->side_dist_x , ray_c->delta_dist_x);
	ray_c->ray_distance = (ray_c->side_dist_x - ray_c->delta_dist_x) * 25;
	if (map.player.x > ray_c->ray_index_x)
	{
	    // printf("west\n");
		ray_c->wall_hit_x = (ray_c->ray_index_x + 1) * 25;
		data->wall_to_draw = (uint32_t *)data->east->pixels;
		// data->wall_to_draw = data->west->pixels;
	}
	else
	{
	    // printf("east\n");
		ray_c->wall_hit_x = ray_c->ray_index_x * 25;
		data->wall_to_draw = (uint32_t *)data->west->pixels;
		// data->wall_to_draw = data->east->pixels;
	}
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
		ray_c->ray_index_y += ray_c->step_y;
		ray_c->side = 1;
	}
}

void	step_pos(t_ray *ray_c, char coor)
{
	if (coor == 'x')
	{
		printf("Going right\n");
		ray_c->step_x = 1;
		ray_c->side_dist_x = (ray_c->ray_index_x + 1.0 - ray_c->unit_x) * ray_c->delta_dist_x;
	}
	else if (coor == 'y')
	{
		printf("Going up\n");
		ray_c->step_y = -1;
		// ray_c->side_dist_y = (ray_c->unit_y - ray_c->ray_index_y) * ray_c->delta_dist_y;
		ray_c->side_dist_y = (ray_c->ray_index_y + 1.0 - ray_c->unit_y) * ray_c->delta_dist_y;
	}
}

void	step_neg(t_ray *ray_c, char coor)
{
	if (coor == 'x')
	{
		printf("Going left\n");
		ray_c->step_x = -1;
		ray_c->side_dist_x = (ray_c->unit_x - ray_c->ray_index_x) * ray_c->delta_dist_x;
	}
	else if (coor == 'y')
	{
		printf("Going down\n");
		ray_c->step_y = 1;
		// ray_c->side_dist_y = (ray_c->ray_index_y + 1.0 - ray_c->unit_y) * ray_c->delta_dist_y;
		ray_c->side_dist_y = (ray_c->unit_y - ray_c->ray_index_y) * ray_c->delta_dist_y;
	}
}

void	set_side_dist(t_ray *ray_c)
{
	if (is_equal(ray_c->ray_dir_x, 0.0))
		ray_c->side_dist_x = DBL_MAX;
	if (ray_c->ray_dir_x < 0.0)
		step_neg(ray_c, 'x');
	else
		step_pos(ray_c, 'x');
	if (is_equal(ray_c->ray_dir_y, 0.0))
		ray_c->side_dist_y = DBL_MAX;
	if (ray_c->ray_dir_y < 0.0)
		step_neg(ray_c, 'y');
	else
		step_pos(ray_c, 'y');
}

void	init_vars(t_map map, t_ray *ray_c)
{
	// printf("ray dir y is %f ray dir x is %f\n", ray_c->ray_dir_y, ray_c->ray_dir_x);
	ray_c->delta_dist_x = sqrt(1 + (ray_c->ray_dir_y * ray_c->ray_dir_y) / (ray_c->ray_dir_x * ray_c->ray_dir_x));
    ray_c->delta_dist_y = sqrt(1 + (ray_c->ray_dir_x * ray_c->ray_dir_x) / (ray_c->ray_dir_y * ray_c->ray_dir_y));
	// ray_c->delta_dist_x = fabs(1 / ray_c->ray_dir_x);
	// ray_c->delta_dist_y = fabs(1 / ray_c->ray_dir_y);
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
	// printf("side dist y is %f delta dist y is %f\n", ray_c->side_dist_y, ray_c->delta_dist_y);
	// printf("side dist x is %f delta dist x is %f\n", ray_c->side_dist_x, ray_c->delta_dist_x);
	if (!ray_c->side)
		vertical_hit(data->map, ray_c, data);
	else
		horizontal_hit(data->map, ray_c, data);
}

void	draw_ray(t_cub3d *data, int x)
{
	int	i;
	int	j;

	j = 0;
	i = 1000 / data->wall_height;
	while (data->start <= data->end)
	{
		draw_pixel(data, x, i * (j * 1000 + x));
		j++;
	}
}

void	set_strip_height(t_cub3d *data, float distance)
{
	if (distance < 1)
		distance = 1;
	data->wall_height = (int)(SCREEN_HEIGHT / (distance/25));
	data->start = -data->wall_height / 2 + SCREEN_HEIGHT / 2;
	if (data->start < 0)
		data->start = 0;
	data->end = data->start + data->wall_height;
	if (data->end >= SCREEN_HEIGHT)
		data->end = SCREEN_HEIGHT - 1;
	// printf("Wall height is %i distance is %f start is %i end is %i\n", data->wall_height, distance, data->start, data->end);
}

void	render_ray(t_cub3d *data, int distance, int ray_index)
{
	set_strip_height(data, distance);
	draw_ray(data, ray_index);
}

// void	fov_cast(t_cub3d *data, t_ray *ray_c, float player_angle)
// {
// 	double	rad;
// 	float	ray;
// 	int		x;
// 	int		y;
// 	int		i;
// 	int index = 0;

// 	ray = 60;
// 	double dir_x = cos(rad);
//     double dir_y = sin(rad);
// 	// double plane_x = -dir_y * 0.6;
//     // double plane_y = dir_x * 0;
// 	// double camera_x = 2 * index / (double)SCREEN_WIDTH - 1;
// 	draw_background(data);
// 	while (ray > 0)
// 	{
// 		ray_c->current_angle = player_angle + 30 + ray;
// 		rad = ray_c->current_angle * M_PI / 180.0;
// 		ray_c->ray_dir_x = cos(rad);
// 		ray_c->ray_dir_y = sin(rad);

// 		ray_cast(data, ray_c);
// 		i = 0;
// 		while (i < ray_c->ray_distance)
// 		{
// 			x = PLAYER_X + (int)(ray_c->ray_dir_x * i);
// 			y = PLAYER_Y - (int)(ray_c->ray_dir_y * i);
// 			if (x > 0 && x < 275 && y > 0 && y < 275)
// 				mlx_put_pixel(data->minimap, x, y, 0xFFFFFF);
// 			i++;
// 		}
// 		render_ray(data, (int)(ray_c->ray_distance), index);
// 		index++;
// 		ray -= .06;
// 	}
// }

void fov_cast(t_cub3d *data, t_ray *ray_c, float player_angle)
{
    int index = 0;
    double rad = player_angle * M_PI / 180.0;
    double dir_x = cos(rad);
    double dir_y = sin(rad);
    // double plane_x = dir_y * 0.6; //fixes fish eye
    // double plane_y = dir_x * 0.6;
    double plane_x = 0.0;
    double plane_y = 0.6;
    draw_background(data);
    for (index = 0; index < 600; index++)
    {
        double camera_x = 2.0 * index / (double)SCREEN_WIDTH - 1.0;
        ray_c->ray_dir_x = dir_x + plane_x * camera_x;
        ray_c->ray_dir_y = dir_y + plane_y * camera_x;
		// printf("dirx is %f dir y is %f #####ray dir x is %f and ray dir y is %f\n", dir_x, dir_y, ray_c->ray_dir_x, ray_c->ray_dir_y);
        ray_cast(data, ray_c);
        // int i = 0;
        // while (i < ray_c->ray_distance)
        // {
        //     cast_fov(data, ray_c, player_angle);
        // }
        render_ray(data, (int)(ray_c->ray_distance), index);
    }
}

// double corrected_distance = ray_c->ray_distance * cos(atan2(ray_c->ray_dir_y, ray_c->ray_dir_x) - rad);

// void	draw_ray(t_cub3d *data, int ray_index)
// {
// 	uint8_t 	tmp2[4];
// 	uint8_t 	*tmp;
// 	int			y;
// 	int			x;
// 	int			i;
// 	int			j;

// 	i = 1000/data->wall_height;
// 	y = 0;
// 	tmp = data->wall_to_draw->pixels;
// 	while (y < 1000)
// 	{
// 		x = 0;
// 		j = y;
// 		while (x < 4)
// 			tmp2[x++] = tmp[j++];
// 		draw_pixel(data, ray_index, tmp2);
// 		y += i * 4;
// 	}
// }