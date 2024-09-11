/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:18:02 by linhnguy          #+#    #+#             */
/*   Updated: 2024/09/10 18:05:59 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>

int create_images(t_minimap *data)
{
	data->background_tex = mlx_load_png("assets/black_bg.png");
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	// data->arrow_tex = mlx_load_png("assets/player_icon.png");
	// data->arrow_png = mlx_texture_to_image(data->mlx, data->arrow_tex);
	// mlx_resize_image(data->arrow_png, 20, 20);
	// mlx_image_to_window(data->mlx, data->arrow_png, 625, 450);
	return (0);
}

void draw_square(t_minimap *data, float y_coor, float x_coor)
{
	int x;
	int y;
	int xx;
	int yy =0;

	
	y = 1;
	while (y < INDEX_HEIGHT)
	{
		if( yy < 0 || yy > 275){

		printf("\n");
		printf("yy is %i\n", yy);
		}
		yy = (int)(y_coor + y - data->offsety + 13);
		x = 1;
		while (x < INDEX_WIDTH)
		{
			xx = (int)(x_coor + x - data->offsetx + 13);
			if (xx < 0)
				xx = 0;
			if (xx > 0 && xx < 275 && yy > 0 && yy < 275)
				mlx_put_pixel(data->background_png, xx, yy, 0x0000FFFF);
			x++;
		}
		y++;
	}
}

int draw_wall(t_minimap *data)
{
	int	i;
	int j;
	int k;
	int y = 0;

	i = data->player->y - 5;
	j = data->player->x - 5;
	k = j;
	while (y < 12)
	{
		if (i >= 0 && !data->map[i])
			break;
		int x = 0;
		j = k;
		while (x < 12)
		{
			if ((i >= 0 && j >= 0) && !data->map[i][j])
				break;
			if ((i >= 0 && j >= 0) && data->map[i][j] == '1') 
				draw_square(data, y * INDEX_HEIGHT, x * INDEX_WIDTH);
			j++;
			x++;
		}
		i++;
		y++;
	}
	return (0);
}

void rotate_point(int *x, int *y, double angle)
{
    double radians = angle * M_PI / 180.0;

    int cx = PLAYER_X;
    int cy = PLAYER_Y;
    
    int new_x = (int)((*x - cx) * cos(radians) - (*y - cy) * sin(radians) + cx);
    int new_y = (int)((*x - cx) * sin(radians) + (*y - cy) * cos(radians) + cy);
    
    *x = new_x;
    *y = new_y;
}

int draw_player(t_minimap *data)
{
	int i = 0;

	i = 0;
	mlx_put_pixel(data->background_png, (int)PLAYER_X, (int)PLAYER_Y, 0xFFFFFF);
	while (i < 6)
	{
		mlx_put_pixel(data->background_png, (int)(PLAYER_X - i), (int)(PLAYER_Y + i), 0xFFFFFF);
		mlx_put_pixel(data->background_png, (int)(PLAYER_X - i), (int)(PLAYER_Y - i), 0xFFFFFF);
		i++;
	}
	return (0);
}

void	rotate_right(t_minimap *data)
{
	mlx_delete_image(data->mlx, data->background_png);
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	draw_wall(data);
	draw_player(data);
}

void	rotate_left(t_minimap *data)
{
	mlx_delete_image(data->mlx, data->background_png);
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	draw_wall(data);
	draw_player(data);
}

void move_left(t_minimap *data)
{
	mlx_delete_image(data->mlx, data->background_png);
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	data->offsetx = data->offsetx - 3;
	if (data->offsetx < 0)
	{
		data->player->x -= 1;
		data->offsetx += 25;
	}
	draw_wall(data);
	draw_player(data);
}

void move_right(t_minimap *data)
{
	mlx_delete_image(data->mlx, data->background_png);
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	data->offsetx = data->offsetx + 3;
	if (data->offsetx > 25)
	{
		data->player->x += 1;
		data->offsetx -= 25;
	}
	draw_wall(data);
	draw_player(data);
	draw_wall(data);
	draw_player(data);
}

void move_down(t_minimap *data)
{
	mlx_delete_image(data->mlx, data->background_png);
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	data->offsety = data->offsety + 3;
	if (data->offsety > 25)
	{
		data->player->y += 1;
		data->offsety -= 25;
	}
	draw_wall(data);
	draw_player(data);
}

void move_up(t_minimap *data)
{
	mlx_delete_image(data->mlx, data->background_png);
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	data->offsety = data->offsety - 3;
	if (data->offsety < 25)
	{
		data->player->y -= 1;
		data->offsety += 25;
	}
	draw_wall(data);
	draw_player(data);
}

void	my_keyhook(mlx_key_data_t keydata, void *game_data)
{
	t_minimap	*data;
	data = (t_minimap *)game_data;
	
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(data->mlx);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		rotate_right(data);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		rotate_left(data);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
		move_up(data);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		move_left(data);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		move_right(data);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
		move_down(data);
}

int init_game(t_minimap *data)
{
	data->mlx = mlx_init(1000, 900, "Cub3D", false);
	create_images(data);
	draw_player(data);
	draw_player(data);
	draw_wall(data);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}

void do_game(t_cub data2)
{
	t_minimap	data;
	data = (t_minimap){0};
	data.map = data2.map.layout;
	data.player = &data2.map.player;
	if (data2.map.orientation == 'E')
		data.p_angle = 0.0;
	else if (data2.map.orientation == 'N')
		data.p_angle = 90.0;
	else if (data2.map.orientation == 'W')
		data.p_angle = 180.0;
	else if (data2.map.orientation == 'S')
		data.p_angle = 270.0;
	data.offsetx = 13;
	data.offsety = 13;
		
	printf("angle is %f\n", data.p_angle);
	for(int i = 0; data.map[i]; i++)
		printf("%s\n", data.map[i]);
	init_game(&data);
}

