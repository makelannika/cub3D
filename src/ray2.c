#include "../include/cub3d.h"

double degree_to_rad(float player_angle)
{
	double rad;
	
	rad = player_angle * M_PI / 180.0;
	return (rad);
}

void	draw_ray(t_cub3d *data, int ray_index)
{
	double	i;
	double	tex_pos;

	ray_index = 999 - ray_index;
	data->ray_c.text_x = 999 - data->ray_c.text_x;
	i = 1.0 * 1000 / data->ray_c.wall_height;
	// printf("%f\n", data->ray_c.text_x);
	tex_pos = (data->ray_c.start - 1000 / 2 + data->ray_c.wall_height / 2) * i;
	while (data->ray_c.start < data->ray_c.end)
	{
		int texY = (int)tex_pos & (1000 - 1);
		tex_pos += i;
		// if (!(data->ray_c.start < 275 && ray_index < 275))
			draw_pixel(data, ray_index, (1000 * texY + data->ray_c.text_x));
		data->ray_c.start++;
	}
}

void fov_cast(t_cub3d *data, t_ray *ray_c)
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	sideDistX;
	double	sideDistY;
	double	perpWallDist;
	int		indexX;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		hit = 0;
	int		side = 0;

	indexX = 0;

	draw_background(data);
	while (indexX < SCREEN_WIDTH)
	{
		hit = 0;
		cameraX = 2 * indexX / (double)SCREEN_WIDTH - 1;
		rayDirX = ray_c->dir_x + ray_c->plane_x * cameraX;
		rayDirY = ray_c->dir_y + ray_c->plane_y * cameraX;
		// printf("ray is %i dirx is %f diry %f\n", indexX, rayDirX, rayDirY);
		mapX = (int)data->ray_c.pos_x;
		mapY = (int)data->ray_c.pos_y;
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
      	double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		// deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
      	// deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (data->ray_c.pos_x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->ray_c.pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (data->ray_c.pos_y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->ray_c.pos_y) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (data->map.grid[mapY][mapX] == '1')
				hit = 1;
		}
		if (side == 0)
		{
			if(mapX > data->ray_c.pos_x)
				data->wall_to_draw = (uint32_t *)data->west->pixels;
			else
				data->wall_to_draw = (uint32_t *)data->east->pixels;
			perpWallDist = (sideDistX - deltaDistX);
		}
		else
		{
			if(mapY > data->ray_c.pos_y)
				data->wall_to_draw = (uint32_t *)data->north->pixels;
			else
				data->wall_to_draw = (uint32_t *)data->south->pixels;
			perpWallDist = (sideDistY - deltaDistY);
		}
		if (perpWallDist < 1)
			perpWallDist = 1;
		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0) 
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;
		
		double wallX;
		if (side == 0)
			wallX = data->ray_c.pos_y + perpWallDist * rayDirY;
		else
			wallX = data->ray_c.pos_x + perpWallDist * rayDirX;
		wallX -= floor((wallX));

		int texX = (int)(wallX * (double)(1000));
		if(side == 0 && rayDirX > 0)
			texX = 1000 - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = 1000 - texX - 1;
		ray_c->wall_height = lineHeight;
		ray_c->start = drawStart;
		ray_c->end = drawEnd;
		ray_c->text_x = texX;
		// printf("wallX = %f\n", wallX);
		draw_ray(data, indexX);
		indexX++;
	}
}
