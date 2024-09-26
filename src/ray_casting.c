/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:01:45 by amakela           #+#    #+#             */
/*   Updated: 2024/09/25 15:54:07 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	is_equal(double a, double b)
{
	return (fabs(a - b) < 1e-9);
}

void	ray_cast(t_cub3d *data, double ray_dir_x, double ray_dir_y)
{
    double delta_dist_x = fabs(1 / ray_dir_x);
    double delta_dist_y = fabs(1 / ray_dir_y);
	float unit_x = data->map.player.pix_x / 25;
	float unit_y = data->map.player.pix_y / 25;
	int ray_index_x = data->map.player.x;
	int	ray_index_y = data->map.player.y;
    int step_x, step_y;
    double side_dist_x, side_dist_y;

	if (is_equal(ray_dir_x, 0.0))
		side_dist_x = DBL_MAX;
	else if (ray_dir_x < 0.0)
    {
        step_x = -1;
        side_dist_x = (unit_x - ray_index_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (ray_index_x + 1.0 - unit_x) * delta_dist_x;
    }
	if (is_equal(ray_dir_y, 0.0))
		side_dist_y = DBL_MAX;
    else if (ray_dir_y < 0.0)
    {
        step_y = -1;
        side_dist_y = (ray_index_y + 1.0 - unit_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (unit_y - ray_index_y) * delta_dist_y;
    }
    // printf("side_dist_x: %f\nside_dist_y: %f\n", side_dist_x, side_dist_y);
    int hit = 0;
    int side;
    while (hit == 0)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            ray_index_x += step_x;
            side = 0;
        }
        else
        {
            side_dist_y += delta_dist_y;
            ray_index_y -= step_y;
            side = 1;
        }
        if (data->map.grid[ray_index_y][ray_index_x] == '1')
            hit = 1;
    }
        if (side == 0) //vertical wall
		{
            data->ray_distance = (side_dist_x - delta_dist_x) * 25;
			if (data->map.player.x > ray_index_x)
			{
				// printf("east");
				ray_c->wall_hit_x = (ray_index_x + 1) * 25;
				data->wall_to_draw = data->ea;
			}
			else
			{
				// printf("west");
				ray_c->wall_hit_x = ray_index_x * 25;
				ray_c->wall_to_draw = data->we;
			}
			ray_c->wall_hit_y = (unit_y + (side_dist_x - delta_dist_x) * ray_dir_y) * 25;
		}
        else // horizontal wall
		{
            ray_c->ray_distance = (side_dist_y - delta_dist_y) * 25;
			if (ray_c->map.player.y > ray_index_y)
			{
				// printf("north");
				ray_c->wall_hit_y = (ray_index_y + 1) * 25;
				ray_c->wall_to_draw = data->no;
			}
			else
			{	
				// printf("south");
				ray_c->wall_hit_y = ray_index_y * 25;
				ray_c->wall_to_draw = data->so;
			}
    		ray_c->wall_hit_x = (unit_x + (side_dist_y - delta_dist_y) * ray_dir_x) * 25;
		}
}

void	set_strip_height(int *start, int *end, int *wall_height, float distance)
{
	*wall_height = (int)distance; 
	printf("wall_height is %i distance is %f\n", *wall_height, distance);
	*start = -*wall_height / 2 + SCREEN_HEIGHT / 2;
	if (start < 0)
		start = 0;
	*end = *wall_height / 2 + SCREEN_HEIGHT / 2;
	if (*end >= SCREEN_HEIGHT)
		*end = SCREEN_HEIGHT - 1;
}

void render_ray(t_cub3d *data, float distance, int ray_index)
{
	int	wall_height;
	int	start;
	int	end;

	set_strip_height(&start, &end, &wall_height, distance);
}

void	fov_cast(t_cub3d *data, float player_angle)
{
	double	rad;
	int		x;
	int		y;
	int		i;
	float	ray;

	ray = 0;
	while (ray < 60)
	{
		double	current_angle = player_angle - 30 + ray;
		rad = current_angle * M_PI / 180.0;
		double	ray_dir_x = cos(rad);
		double	ray_dir_y = sin(rad);
		ray_cast(data, ray_dir_x, ray_dir_y);
		i = 0;
		while (i < data->ray_distance)
		{
			x = PLAYER_X + (int)(ray_dir_x * i);
			y = PLAYER_Y - (int)(ray_dir_y * i);
			if (x > 0 && x < 275 && y > 0 && y < 275)
				mlx_put_pixel(data->minimap, x, y, 0xFFFFFF);
			i++;
		}
		// printf("ray is %f hit x is %f hit y is %f px is %f py is %f\n", ray, data->wall_hit_x, data->wall_hit_y, data->map.player.pix_x, data->map.player.pix_y);
		// printf("hit x is %f hit y is %f px is %f py is %f\n", data->wall_hit_x, data->wall_hit_y, data->map.player.pix_x, data->map.player.pix_y);
		render_ray(data, (int)(SCREEN_HEIGHT / (data->ray_distance)), SCREEN_WIDTH / 60 * ray);
		ray += .06;
	}
}
