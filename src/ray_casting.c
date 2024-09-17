/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:01:45 by amakela           #+#    #+#             */
/*   Updated: 2024/09/12 18:06:58 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include "../include/cub3d.h"

// void cast_1000(t_minimap *data, float player_angle)
// {
// 	double	rad;
// 	int		ray;

// 	ray = 0;
// 	while (ray < 1000)
//     {
//         double current_angle = player_angle - 30 + ray * 60 / 1000;
//         rad = current_angle * M_PI / 180.0;
//         double ray_dir_x = cos(rad);
//         double ray_dir_y = sin(rad);
// 		ray++;
// 	}
// }
static bool	is_equal(double a, double b)
{
	return (fabs(a - b) < 1e-9);
}

float	ray_cast(t_minimap *data, double ray_dir_x, double ray_dir_y)
{

    double wall_distance;
    double delta_dist_x = fabs(1 / ray_dir_x);
    double delta_dist_y = fabs(1 / ray_dir_y);
	float unit_x = data->player.pix_x / 25;
	float unit_y = data->player.pix_y / 25;
	int ray_index_x = data->player.x;
	int	ray_index_y = data->player.y;
    int step_x, step_y;
    double side_dist_x, side_dist_y;

	printf("playerPixX is %f  playerPixy is %f  offset is %i\n", data->player.pix_x, data->player.pix_y, data->offsety);
    // printf("rayDY is %f\n", ray_dir_y);
	if (is_equal(ray_dir_x, 0.0))
		side_dist_x = DBL_MAX;
	else if (ray_dir_x < 0.0)
    {
        printf("ere1\n");
        step_x = -1;
        side_dist_x = (unit_x - ray_index_x) * delta_dist_x;
    }
    else
    {
        printf("ere2\n");
        step_x = 1;
        side_dist_x = (ray_index_x + 1.0 - unit_x) * delta_dist_x;
    }
	if (is_equal(ray_dir_y, 0.0))
		side_dist_y = DBL_MAX;
    else if (ray_dir_y < 0)
    {
        printf("ere3\n");
        step_y = -1;
        side_dist_y = (unit_y - ray_index_y) * delta_dist_y;
    }
    else
    {
        printf("ere4\n");
        step_y = 1;
        side_dist_y = (ray_index_y + 1.0 - unit_y) * delta_dist_y;
    }
	printf("unit_y is %f ray_index is %i\n", unit_y, ray_index_y);
	// printf("side_dist_x=%f, side_dist_y=%f in pixels\n", side_dist_x, side_dist_y * 25);
	printf("side_dist_y= %f in pixels\n", side_dist_y * 25);
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
		
        if (data->map[ray_index_y][ray_index_x] == '1')
        {
			printf("RAY is looking at x %i y %i\n", ray_index_x, ray_index_y);
            hit = 1;
        }
    }
   	if (side == 0) // Vertical wall hit
    {
        wall_distance = side_dist_x - delta_dist_x;
    }
    else // Horizontal wall hit
    {
        wall_distance = side_dist_y - delta_dist_y;
    }
	// printf("side: %i\nray index x: %i pixel x: %f stepx: %i ray dir x: %f\n", side, ray_index_x, unit_x, step_x, ray_dir_x);
	// printf("ray index y: %i pixel y: %f stepy: %i ray dir y: %f\n", ray_index_y, unit_y, step_y, ray_dir_y);
	return (wall_distance * 25);
}

// float	ray_cast(t_minimap *data, double ray_dir_x, double ray_dir_y)
// {

// }

void	fov_cast(t_minimap *data, float player_angle)
{
	double	rad;
	int		x;
	int		y;
	int		i;
	// float	ray;
	float	distance;

	// ray = 0;
	// while (ray < 60)
	// {
	// 	double	current_angle = player_angle - 30 + ray;
		rad = player_angle * M_PI / 180.0;
		double	ray_dir_x = cos(rad);
		double	ray_dir_y = sin(rad);
		printf("\nangle is %f dx is %f dy is %f\n", player_angle, ray_dir_x, ray_dir_y);
		distance = ray_cast(data, ray_dir_x, ray_dir_y);
		i = 0;
		printf("distance is %f\n", distance);
		while (i < distance)
		// while (i < 194)
		{
			x = PLAYER_X + (int)(ray_dir_x * i);
			y = PLAYER_Y - (int)(ray_dir_y * i);
			if (x > 0 && x < 275 && y > 0 && y < 275)
				mlx_put_pixel(data->background_png, x, y, 0xFFFFFF);
			i++;
		}
		// ray += .06;
	// }
}
