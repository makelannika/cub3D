/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:18:02 by linhnguy          #+#    #+#             */
/*   Updated: 2024/09/08 16:45:24 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int create_images(t_minimap *data)
{
	data->background_tex = mlx_load_png("assets/black_bg.png");
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_resize_image(data->background_png, 275, 275);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	// data->arrow_tex = mlx_load_png("assets/player_icon.png");
	// data->arrow_png = mlx_texture_to_image(data->mlx, data->arrow_tex);
	// mlx_resize_image(data->arrow_png, 20, 20);
	// mlx_image_to_window(data->mlx, data->arrow_png, 625, 450);
	return (0);
}

void draw_square(t_minimap *data, float y_coor, float x_coor)
{
	int i;
	int j;

	i = 1;
	while (i < INDEX_HEIGHT)
	{
		j = 1;
		while (j < INDEX_WIDTH)
		{
			mlx_put_pixel(data->background_png, (int)(x_coor + j), (int)(y_coor + i), 0x00FFFF);
			j++;
		}
		i++;
	}
}

int draw_wall(t_minimap *data, int start_x, int star)
{
	int	map_y;
	int map_x;
	int minimap_y = 0;
	int	minimap_x = 0;
	int x_start;

	map_y = data->player->y - 5;
	map_x = data->player->x - 5;
	x_start = map_x;
	while (minimap_y < MINIMAP_HEIGHT)
	{
		if (map_y >= 0 && !data->map[map_y])
			break;
		minimap_x = 0;
		map_x = x_start;
		while (minimap_x < MINIMAP_WIDTH)
		{
			if ((map_y >= 0 && map_x >= 0) && !data->map[map_y][map_x])
				break;
			if ((map_y >= 0 && map_x >= 0) && data->map[map_y][map_x] == '1')
				draw_square(data, minimap_y * INDEX_HEIGHT, minimap_x * INDEX_WIDTH);
			map_x++;
			minimap_x++;
		}
		map_y++;
		minimap_y++;
	}
	return (0);
}

// int draw_player(t_minimap *data)
// {
// 	int i = 0;

// 	i = 0;
// 	mlx_put_pixel(data->background_png, (int)PLAYER_X, (int)PLAYER_Y, 0xFFFFFF);
// 	while (i < 6)
// 	{
// 		mlx_put_pixel(data->background_png, (int)(PLAYER_X - i), (int)(PLAYER_Y + i), 0xFFFFFF);
// 		mlx_put_pixel(data->background_png, (int)(PLAYER_X - i), (int)(PLAYER_Y - i), 0xFFFFFF);
// 		i++;
// 	}
// 	return (0);
// }

void rotate_point(int *x, int *y, double angle)
{
    double radians = angle * M_PI / 180.0;  // Convert degrees to radians
    int cx = PLAYER_X;
    int cy = PLAYER_Y;
    
    int new_x = (int)((*x - cx) * cos(radians) - (*y - cy) * sin(radians) + cx);
    int new_y = (int)((*x - cx) * sin(radians) + (*y - cy) * cos(radians) + cy);
    
    *x = new_x;
    *y = new_y;
}

int draw_player(t_minimap *data, double angle)
{
    int i;
    int x, y;

    mlx_put_pixel(data->background_png, PLAYER_X, PLAYER_Y, 0xFFFFFF);
    for (i = 0; i < 6; i++)
    {
        x = PLAYER_X - i;
        y = PLAYER_Y + i;
        rotate_point(&x, &y, angle);
        mlx_put_pixel(data->background_png, x, y, 0xFFFFFF);
        x = PLAYER_X - i;
        y = PLAYER_Y - i;
        rotate_point(&x, &y, angle);
        mlx_put_pixel(data->background_png, x, y, 0xFFFFFF);
    }
    return (0);
}

void	rotate_right(t_minimap *data)
{
	double	degree;

	degree = 15;
	draw_player(data, degree);
}

void	rotate_left(t_minimap *data)
{
	double	degree;

	degree = -15;
	draw_player(data, degree);
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
	// if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
	// 	move_up(data);
	// if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
	// 	move_left(data);
	// if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
	// 	move_right(data);
	// if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
	// 	move_down(data);
}

int init_game(t_minimap *data)
{
	data->mlx = mlx_init(1000, 900, "Cub3D", false);
	create_images(data);
	draw_player(data, 100);
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
	data.map_width = data2.map.width;
	data.map_height = data2.map.height;
	data.player = &data2.map.player;

	for(int i = 0; data.map[i]; i++)
		printf("%s\n", data.map[i]);
	init_game(&data);
}

