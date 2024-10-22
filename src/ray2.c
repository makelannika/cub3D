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
	// float	counter;
	double	tex_pos;

	i = 1.0 * 1000 / data->ray_c.wall_height;
	tex_pos = (data->ray_c.start - 1000 / 2 + data->ray_c.wall_height / 2) * i;
	// tex_pos = (data->ray_c.start - (-data->ray_c.wall_height / 2 + SCREEN_HEIGHT / 2)) * i;

	// counter = 0;
	// if (i < 1)
	// 	i = 1;
	// printf("texX = %d\n", data->ray_c.text_x);
	// printf("wall height = %d i = %f\n", data->ray_c.wall_height, i);
	while (data->ray_c.start < data->ray_c.end)
	{
		// printf("text_x is %i\n", data->ray_c.text_x);
		// printf("ray index is %i\n", ray_index);
		int texY = (int)tex_pos & (1000 - 1);
		tex_pos += i;
		// printf("texY = %d\n", texY);
		// if (!(data->ray_c.start < 275 && ray_index < 275))
			draw_pixel(data, ray_index, (1000 * texY + data->ray_c.text_x));
			// draw_pixel(data, ray_index, ((int)counter * 1000) + data->ray_c.text_x);
		data->ray_c.start++;
		// counter += i;
	}
}

void fov_cast(t_cub3d *data, t_ray *ray_c, float player_angle)
{
	double	rad;
	// double	dirX;
	// double	dirY;
	// double	planeX;
	// double	planeY;
	// double	time = 0;
	// double	oldtime = 0;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	sideDistX;
	double	sideDistY;
	double	perpWallDist;
	// double deltaDistX;
	// double deltaDistY;
	int		indexX;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		hit = 0;
	int		side = 0;

	// rad = degree_to_rad(player_angle);
	// dirX = cos(rad);
	// dirY = sin(rad);
	// ray_c->dir_x = cos(rad);
	// ray_c->dir_y = sin(rad);
	// printf("player x is %i posx is %f dirX is %f \n", data->map.player.x, data->ray_c.pos_x, dirX);
	// planeX = 0.0;
	// planeY = 0.66;
	indexX = 0;

	// gettimeofday(&data->old_time, NULL);
	draw_background(data);
	while (indexX < SCREEN_WIDTH)
	{
		hit = 0;
		cameraX = 2 * indexX / (double)SCREEN_WIDTH - 1;
		// printf("camera x is %f\n", cameraX);
		rayDirX = ray_c->dir_x + ray_c->plane_x * cameraX;
		rayDirY = ray_c->dir_y + ray_c->plane_y * cameraX;
		// printf("ray dir x is %f ray dir y is %f\n", rayDirX, rayDirY);
		mapX = (int)data->ray_c.pos_x;
		mapY = (int)data->ray_c.pos_y;
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
      	double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		// deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
      	// deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
		if (rayDirX < 0)
		{
			// printf("step\n");
			stepX = -1;
			sideDistX = (data->ray_c.pos_x - mapX) * deltaDistX;
		}
		else
		{
			// printf("step1\n");
			stepX = 1;
			sideDistX = (mapX + 1.0 - data->ray_c.pos_x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			// printf("step2\n");
			stepY = -1;
			sideDistY = (data->ray_c.pos_y - mapY) * deltaDistY;
		}
		else
		{
			// printf("step3\n");
			stepY = 1;
			sideDistY = (mapY + 1.0 - data->ray_c.pos_y) * deltaDistY;
		}
		while (hit == 0)
		{
			// printf("side x %f side y is %f\n", sideDistX, sideDistY);
			if (sideDistX < sideDistY)
			{
			// printf("here\n");
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
			// printf("here2\n")?;
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (data->map.grid[mapY][mapX] == '1')
				hit = 1;
		}
		if (side == 0)
		{
			// printf("here3\n");
			perpWallDist = (sideDistX - deltaDistX);
		}
		else
		{
			// printf("here4\n");
			perpWallDist = (sideDistY - deltaDistY);
		}
		// printf("wall dist is %f\n", perpWallDist);
		int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);
		// if (lineHeight > 1000)
		// 	lineHeight = 1000;
		int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawStart < 0) 
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
		if (drawEnd >= SCREEN_HEIGHT)
			drawEnd = SCREEN_HEIGHT - 1;
		//calculate value of wallX
		double wallX;
		if (side == 0)
		{
			// printf("here 1\n");
			wallX = data->ray_c.pos_y + perpWallDist * rayDirY;
		}
		else
		{
			// printf("posx = %f perpdist = %f raydirx = %f\n", posX, perpWallDist, rayDirX);
			wallX = data->ray_c.pos_x + perpWallDist * rayDirX;
		}
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(1000));
		if(side == 0 && rayDirX > 0)
			texX = 1000 - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = 1000 - texX - 1;
		ray_c->wall_height = lineHeight;
		ray_c->start = drawStart;
		ray_c->end = drawEnd;
		ray_c->text_x = texX;
		data->wall_to_draw = (uint32_t *)data->south->pixels;
		// printf("wallX = %f\n", wallX);
		draw_ray(data, indexX);
		indexX++;
		// printf("lineHeight = %d\n", lineHeight);
	}
}
