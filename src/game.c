/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:18:02 by linhnguy          #+#    #+#             */
/*   Updated: 2024/09/04 17:30:18 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int create_images(t_minimap *data)
{
	data->background_tex = mlx_load_png("assets/minimap_background.png");
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_resize_image(data->background_png, 250, 250);
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

	i = 0;
	while (i < data->index_height)
	{
		j = 0;
		while (j < data->index_width)
		{
			mlx_put_pixel(data->background_png, (int)(x_coor + j), (int)(y_coor + i), 0xFFFFFF);
			j++;
		}
		i++;
	}
}

int draw_wall(t_minimap *data)
{
	int	i;
	int j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				draw_square(data, i * data->index_height, j * data->index_width);
			j++;
		}
		i++;
	}
	return (0);
}

int draw_player(t_minimap *data)
{
	int x_index = 2;
	int y_index = 1;
	data->player_x = (data->index_width * x_index) + (data->index_width / 2);
	data->player_y = (data->index_height * y_index) + (data->index_height / 2);
	int i = 0;

	i = 0;
	while (i < 10)
	{
		mlx_put_pixel(data->background_png, (int)(data->player_x - i), (int)(data->player_y + i), 0xFFFFFF);
		mlx_put_pixel(data->background_png, (int)(data->player_x - i), (int)(data->player_y - i), 0xFFFFFF);
		i++;
	}
	return (0);
}

int init_game(t_minimap *data)
{
	data->mlx = mlx_init(1000, 900, "Cub3D", false);
	create_images(data);
	draw_player(data);
	draw_wall(data);
	mlx_loop(data->mlx);
	return (0);
}

int main()
{
	t_minimap	data;
	data = (t_minimap){0};
	data.map = malloc(sizeof(char *)  * 4);
	data.map[0] = ft_strdup("1111");
	data.map[1] = ft_strdup("10E1");
	data.map[2] = ft_strdup("1111");
	data.map[3] = NULL;
	data.index_height = 250/3;
	data.index_width = 250/4;
	data.map_width = 4;
	data.map_height = 3;

	for(int i = 0; i < 3; i++)
		printf("%s\n", data.map[i]);
	init_game(&data);
}

// void	my_keyhook(mlx_key_data_t keydata, void *game_data)
// {
// 	t_data			*data;

// 	data = (t_data *)game_data;
// 	if (data->is_end == true)
// 		return ;
// 	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
// 		mlx_close_window(data->mlx);
// 	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
// 		move_up(data);
// 	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
// 		move_left(data);
// 	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
// 		move_right(data);
// 	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
// 		move_down(data);
// }