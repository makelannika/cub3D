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
            hit = 1;
    }
        if (side == 0)
            wall_distance = side_dist_x - delta_dist_x;
        else
            wall_distance = side_dist_y - delta_dist_y;
    return (wall_distance * 25);
}

void render_ray(t_minimap *data, int wall_height, int ray_index)
{
	int	start;
	int	end;
	int	x;
	int	y;

	x = 0;
	y = 0;

	start = -wall_height / 2 + SCREEN_HEIGHT / 2;
	end = wall_height / 2 + SCREEN_HEIGHT / 2;

	int floor [3] = {220, 100, 0};
	int	ceingling [3] = {225, 30, 0};
	mlx_texture_t	*wt;
	mlx_image_t		*wi;

	wt = mlx_load_png("assets/grayMarble.png");
	wi = mlx_texture_to_image(data->mlx, data->background_tex);

	
}

void	fov_cast(t_minimap *data, float player_angle)
{
	double	rad;
	int		x;
	int		y;
	int		i;
	float	ray;
	float	distance;

	ray = 0;
	while (ray < 60)
	{
		double	current_angle = player_angle - 30 + ray;
		rad = current_angle * M_PI / 180.0;
		double	ray_dir_x = cos(rad);
		double	ray_dir_y = sin(rad);
		distance = ray_cast(data, ray_dir_x, ray_dir_y);
		i = 0;
		while (i < distance)
		{
			x = PLAYER_X + (int)(ray_dir_x * i);
			y = PLAYER_Y - (int)(ray_dir_y * i);
			if (x > 0 && x < 275 && y > 0 && y < 275)
				mlx_put_pixel(data->background_png, x, y, 0xFFFFFF);
			i++;
		}
		render_ray(data, (int)(SCREEN_HEIGHT / distance), SCREEN_WIDTH / 60 * ray);
		ray += .06;
	}
}
