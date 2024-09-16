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


float	ray_cast(t_minimap *data, double ray_dir_x, double ray_dir_y)
{

    double wall_distance;
    double delta_dist_x = fabs(1 / ray_dir_x);
    double delta_dist_y = fabs(1 / ray_dir_y);
	float pix_x = (data->player.pix_x + (data->offsetx)) / 25;
	float pix_y = (data->player.pix_y + (data->offsety)) / 25;
	int ray_index_x = data->player.x;
	int	ray_index_y = data->player.y;
    int step_x, step_y;
    double side_dist_x, side_dist_y;

    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (pix_x - ray_index_x) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = (ray_index_x + 1.0 - pix_x) * delta_dist_x;
    }
    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (pix_y - ray_index_y) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = (ray_index_y + 1.0 - pix_y) * delta_dist_y;
    }

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
            ray_index_y += step_y;
            side = 1;
        }
		
		printf("y is %i x is %i char is %c\n", ray_index_y,
		ray_index_x, data->map[ray_index_y][ray_index_x]);
        if (data->map[ray_index_y][ray_index_x] == '1')
        {
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
	printf("side: %i\nray index x: %i pixel x: %f stepx: %i ray dir x: %f\n", side, ray_index_x, pix_x, step_x, ray_dir_x);
	printf("ray index y: %i pixel y: %f stepy: %i ray dir y: %f\n", ray_index_y, pix_y, step_y, ray_dir_y);
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
		printf("\nangle is %f\n", player_angle);
		distance = ray_cast(data, ray_dir_x, ray_dir_y);
		i = 0;
		printf("distance is %f\n", distance);
		while (i < distance)
		// while (i < 194)
		{
			x = PLAYER_X + (int)(ray_dir_x * i);
			y = PLAYER_Y + (int)(ray_dir_y * i);
			if (x > 0 && x < 275 && y > 0 && y < 275)
				mlx_put_pixel(data->background_png, x, y, 0xFFFFFF);
			i++;
		}
		// ray += .06;
	// }
}
