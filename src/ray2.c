#include "../include/cub3d.h"

double degree_to_rad(float player_angle)
{
	double rad;
	
	rad = player_angle * M_PI / 180.0;
	return (rad);
}

void	draw_ray(t_cub3d *data, t_ray *ray_c, int screen_x)
{
	screen_x = 999 - screen_x; /* screen x index */
	ray_c->txtr_x = 999 - ray_c->txtr_x; /* texture x index */
	ray_c->increment = 1.0 * SCREEN_HEIGHT / ray_c->wall_height; /* increment */
	ray_c->txtr_y = 0;
	while (ray_c->start <= ray_c->end)
	{
		// if (!(ray_c->start < 275 && screen_x < 275))
		if (ray_c->start >= 0 && ray_c->start < SCREEN_HEIGHT)
			draw_pixel(data, screen_x, (1000 * (int)(ray_c->txtr_y) + ray_c->txtr_x));
		ray_c->txtr_y += ray_c->increment;
		ray_c->start++;
	}
}

void	init_vars(t_ray *ray_c)
{
	ray_c->hit = 0;
	ray_c->camera_x = 2 * ray_c->screen_x / (double)SCREEN_WIDTH - 1;
	ray_c->ray_dir_x = ray_c->dir_x + ray_c->plane_x * ray_c->camera_x;
	ray_c->ray_dir_y = ray_c->dir_y + ray_c->plane_y * ray_c->camera_x;
	ray_c->map_x = (int)ray_c->pos_x;
	ray_c->map_y = (int)ray_c->pos_y;
	ray_c->delta_dist_x = (ray_c->ray_dir_x == 0) ? 1e30 : fabs(1 / ray_c->ray_dir_x);
	ray_c->delta_dist_y = (ray_c->ray_dir_y == 0) ? 1e30 : fabs(1 / ray_c->ray_dir_y);
}

void fov_cast(t_cub3d *data, t_ray *ray_c)
{
	draw_background(data);
	ray_c->side = 0;
	ray_c->screen_x = 0;
	while (ray_c->screen_x < SCREEN_WIDTH)
	{
		init_vars(ray_c);
		if (ray_c->ray_dir_x < 0)
		{
			ray_c->step_x = -1;
			ray_c->side_dist_x = (ray_c->pos_x - ray_c->map_x) * ray_c->delta_dist_x;
		}
		else
		{
			ray_c->step_x = 1;
			ray_c->side_dist_x = (ray_c->map_x + 1.0 - ray_c->pos_x) * ray_c->delta_dist_x;
		}
		if (ray_c->ray_dir_y < 0)
		{
			ray_c->step_y = -1;
			ray_c->side_dist_y = (ray_c->pos_y - ray_c->map_y) * ray_c->delta_dist_y;
		}
		else
		{
			ray_c->step_y = 1;
			ray_c->side_dist_y = (ray_c->map_y + 1.0 - ray_c->pos_y) * ray_c->delta_dist_y;
		}
		while (!ray_c->hit)
		{
			if (ray_c->side_dist_x < ray_c->side_dist_y)
			{
				ray_c->side_dist_x += ray_c->delta_dist_x;
				ray_c->map_x += ray_c->step_x;
				ray_c->side = 0;
			}
			else
			{
				ray_c->side_dist_y += ray_c->delta_dist_y;
				ray_c->map_y += ray_c->step_y;
				ray_c->side = 1;
			}
			if (data->map.grid[ray_c->map_y][ray_c->map_x] == '1')
				ray_c->hit = 1;
		}
		if (ray_c->side == 0)
		{
			if(ray_c->map_x > ray_c->pos_x)
				data->wall_to_draw = (uint32_t *)data->west->pixels;
			else
				data->wall_to_draw = (uint32_t *)data->east->pixels;
			ray_c->distance = (ray_c->side_dist_x - ray_c->delta_dist_x);
		}
		else
		{
			if(ray_c->map_y > ray_c->pos_y)
				data->wall_to_draw = (uint32_t *)data->north->pixels;
			else
				data->wall_to_draw = (uint32_t *)data->south->pixels;
			ray_c->distance = (ray_c->side_dist_y - ray_c->delta_dist_y);
		}
		// if (ray_c->distance < 1)
		// 	ray_c->distance = 1;
		ray_c->wall_height = (int)(SCREEN_HEIGHT / ray_c->distance);
		ray_c->start = -ray_c->wall_height / 2 + SCREEN_HEIGHT / 2;
		// if (ray_c->start < 0) 
		// 	ray_c->start = 0;
		ray_c->end = ray_c->wall_height / 2 + SCREEN_HEIGHT / 2;
		// if (ray_c->end >= SCREEN_HEIGHT)
		// 	ray_c->end = SCREEN_HEIGHT - 1;
		
		if (ray_c->side == 0)
		{
			// printf("fuck\n");
			ray_c->wall_x = ray_c->pos_y + ray_c->distance * ray_c->ray_dir_y;
		}
		else
		{
			// printf("here\n");
			ray_c->wall_x = ray_c->pos_x + ray_c->distance * ray_c->ray_dir_x;
		}
		ray_c->wall_x -= floor((ray_c->wall_x));

		ray_c->txtr_x = (int)(ray_c->wall_x * (double)(1000));
		// printf("ray = %d, posY = %f, distance = %f, dirY = %f, wallx = %f, textx = %d\n", ray_c->screen_x,ray_c->pos_y, ray_c->distance, ray_c->ray_dir_y, ray_c->wall_x, ray_c->txtr_x);
		if(ray_c->side == 0 && ray_c->ray_dir_x > 0)
			ray_c->txtr_x = 1000 - ray_c->txtr_x - 1;
		if(ray_c->side == 1 && ray_c->ray_dir_y < 0)
			ray_c->txtr_x = 1000 - ray_c->txtr_x - 1;
		// ray_c->txtr_x = ray_c->txtr_x;
		draw_ray(data, ray_c, ray_c->screen_x);
		ray_c->screen_x++;
	}
}
