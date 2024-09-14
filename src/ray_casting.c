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
    double delta_dist_x = fabs(25 / ray_dir_x);
    double delta_dist_y = fabs(25 / ray_dir_y);
	float pix_x = data->player.pix_x;
	float pix_y = data->player.pix_y;
	int p_index_x = data->player.x;
	int	p_index_y = data->player.y;
    int step_x, step_y;
    double side_dist_x, side_dist_y;

    // Determine the step direction and initial side distances
    if (ray_dir_x < 0)
    {
        step_x = -1;
        side_dist_x = (pix_x - p_index_x * INDEX_WIDTH) * delta_dist_x;
    }
    else
    {
        step_x = 1;
        side_dist_x = ((p_index_x + 1.0) * INDEX_WIDTH - pix_x) * delta_dist_x;
    }
    if (ray_dir_y < 0)
    {
        step_y = -1;
        side_dist_y = (pix_y - p_index_y * INDEX_HEIGHT) * delta_dist_y;
    }
    else
    {
        step_y = 1;
        side_dist_y = ((p_index_y + 1.0) * INDEX_HEIGHT - pix_y) * delta_dist_y;
    }

    int hit = 0;
    int side;
    while (hit == 0)
    {
        if (side_dist_x < side_dist_y)
        {
            side_dist_x += delta_dist_x;
            p_index_x += step_x;
            side = 0; // Hit a vertical wall
        }
        else
        {
            side_dist_y += delta_dist_y;
            p_index_y += step_y;
            side = 1; // Hit a horizontal wall
        }
		printf("y is %i x is %i char is %c\n", p_index_y,
		p_index_x, data->map[p_index_y][p_index_x]);
        if (data->map[p_index_y][p_index_x] == '1')
        {
            hit = 1;
        }
    }
   if (side == 0)
    {
        wall_distance = (p_index_x - pix_x / 25 + (1 - step_x) / 2) / ray_dir_x;
    }
    else
    {
        wall_distance = (p_index_y - pix_y / 25 + (1 - step_y) / 2) / ray_dir_y;
    }
	return (wall_distance * 25);
}

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
