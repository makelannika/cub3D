/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 23:19:25 by amakela           #+#    #+#             */
/*   Updated: 2024/09/23 00:28:59 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	is_equal(double a, double b)
{
	return (fabs(a - b) < 1e-9);
}

void    horizontal_hit(t_map map, t_ray *ray_c, t_cub3d *data)
{
    ray_c->ray_distance = (ray_c->side_dist_y - ray_c->delta_dist_y) * 25;
    if (map.player.y > ray_c->ray_index_y)
    {
    //     printf("north\n");
        ray_c->wall_hit_y = (ray_c->ray_index_y + 1) * 25;
		data->wall_to_draw = data->no;
    }
    else
    {
    //     printf("south\n");
        ray_c->wall_hit_y = ray_c->ray_index_y * 25;
		data->wall_to_draw = data->so;
    }
    ray_c->wall_hit_x = (ray_c->unit_x + (ray_c->side_dist_y - ray_c->delta_dist_y) * ray_c->ray_dir_x) * 25;
}

 void   vertical_hit(t_map map, t_ray *ray_c, t_cub3d *data)
 {
    ray_c->ray_distance = (ray_c->side_dist_x - ray_c->delta_dist_x) * 25;
    if (map.player.x > ray_c->ray_index_x)
    {
    //     printf("west\n");
        ray_c->wall_hit_x = (ray_c->ray_index_x + 1) * 25;
		data->wall_to_draw = data->we;
    }
    else
    {
    //     printf("east\n");
        ray_c->wall_hit_x = ray_c->ray_index_x * 25;
		data->wall_to_draw = data->ea;
    }
    ray_c->wall_hit_y = (ray_c->unit_y + (ray_c->side_dist_x - ray_c->delta_dist_x) * ray_c->ray_dir_y) * 25;
 }
 
void    forward(t_ray *ray_c, char coor)
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

void    step_pos(t_ray *ray_c, char coor)
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

void    step_neg(t_ray *ray_c, char coor)
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

void    set_side_dist(t_ray *ray_c)
{
	if (is_equal(ray_c->ray_dir_x, 0.0))
		ray_c->side_dist_x = DBL_MAX;
	else if (ray_c->ray_dir_x < 0.0)
        step_neg(ray_c, 'x');
    else
        step_pos(ray_c, 'x');
	if (is_equal(ray_c->ray_dir_y, 0.0))
		ray_c->side_dist_y = DBL_MAX;
    else if (ray_c->ray_dir_y < 0.0)
        step_neg(ray_c, 'y');
    else
        step_pos(ray_c, 'y');
}

void    init_vars(t_map map, t_ray *ray_c)
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
        vertical_hit(data->map, ray_c, data);
    else
        horizontal_hit(data->map, ray_c, data);
	// printf("distance is %f\n", ray_c->ray_distance);
}

int rgba_to_hex(int r, int g, int b, int a)
{
    return (r << 24) | (g << 16) | (b << 8) | a;
}

void	draw_pixel(t_cub3d *data, int y, int x, uint8_t *tmp2)
{
	for (int i = 0; i < 4; i++)
		printf("pixel is %i\n", tmp2[i]);
	int color = rgba_to_hex(tmp2[0], tmp2[1], tmp2[2],tmp2[3]);
	mlx_put_pixel(data->mlx,y, x, color);
}

int	draw_ray(t_cub3d *data, int ray_index)
{
	uint8_t 	tmp2[4];
	mlx_image_t *tmp;
	int			y;
	int			x;
	int i;
	int j;
	int line = 0;

	i = 1000/data->wall_height;
	y = 0;
	tmp = data->wall_to_draw;
	while (y < 1000)
	{
		x = 0;
		while (x < 4)
		{	
			j = y;
			tmp2[x++] = tmp->pixels[j++];
		}
		draw_pixel(data, y, ray_index, tmp2);
		y += i * 4;
	}

	return (0);
}

void	set_strip_height(t_cub3d *data, float distance)
{
	data->wall_height = (int)distance;
	// data->wall_height = (int)(SCREEN_HEIGHT / distance);

	if (data->wall_height > 999)
		data->wall_height = 1000;
	data->start = -distance / 2 + SCREEN_HEIGHT / 2;
	if (data->start < 0)
		data->start = 0;
	data->end = distance/ 2 + SCREEN_HEIGHT / 2;
	if (data->end >= SCREEN_HEIGHT)
		data->end = SCREEN_HEIGHT - 1;
	// printf(" start is %i end is %i\n", *start, *end);
}

void render_ray(t_cub3d *data, float distance, int ray_index)
{
	set_strip_height(data, distance);
	if (draw_ray(data, ray_index))
		return; //do some shit;

}


void	fov_cast(t_cub3d *data, t_ray *ray_c, float player_angle)
{
	double	rad;
	float	ray;
	int		x;
	int		y;
	int		i;

	ray = 0;
	int s = 0;
	while (ray < 60)
	{
		// ray_c->current_angle = player_angle - 5 + ray;
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
		// render_ray(data, (int)(SCREEN_HEIGHT / ray_c->ray_distance * cos(fabs((ray - 5) * M_PI / 180.0))), SCREEN_WIDTH / 5 * ray);
		// render_ray(data, (int)(SCREEN_HEIGHT / ray_c->ray_distance * cos((ray - 30) * M_PI / 180.0)), SCREEN_WIDTH / 60 * ray);
		render_ray(data, (int)(SCREEN_HEIGHT / ray_c->ray_distance), SCREEN_WIDTH / 60 * ray);
		// ray += 1;
		ray += .06;
	}
}
