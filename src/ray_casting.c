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

void	ray_cast(t_minimap *data, float player_angle)
{
	double	rad;
	int		x;
	int		y;
	int		i;
	int		ray;

	ray = 0;
	while (ray < 60)
	{
		double	current_angle = player_angle - 30 + ray;
		rad = current_angle * M_PI / 180.0;
		double	ray_dir_x = cos(rad);
		double	ray_dir_y = sin(rad);
		i = 0;
		while (i < 194)
		{
			x = PLAYER_X + (int)(ray_dir_x * i);
			y = PLAYER_Y + (int)(ray_dir_y * i);
			if (x > 0 && x < 275 && y > 0 && y < 275)
				mlx_put_pixel(data->background_png, x, y, 0xFFFFFF);
			i++;
		}
		ray++;
	}
}
