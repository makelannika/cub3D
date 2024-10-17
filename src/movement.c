/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:45:22 by amakela           #+#    #+#             */
/*   Updated: 2024/09/27 19:34:55 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_left(t_cub3d *data)
{
	data->map.player.pix_x += data->ray_c.dir_y * -1 * 3;
	data->map.player.pix_y += data->ray_c.dir_x * -1 * 3;
	data->map.offsetx += data->ray_c.dir_y * -1 * 3;
	data->map.offsety += data->ray_c.dir_x * -1 * 3;
	if (data->map.offsetx < 0)
	{
		data->map.player.x -= 1;
		data->map.offsetx += 25;
	}
	if (data->map.offsetx > 24)
	{
		data->map.player.x += 1;
		data->map.offsetx -= 25;
	}
	if (data->map.offsety < 0)
	{
		data->map.player.y -= 1;
		data->map.offsety += 25;
	}
	if (data->map.offsety > 24)
	{
		data->map.player.y += 1;
		data->map.offsety -= 25;
	}
	fov_cast(data, &data->ray_c, data->map.p_angle);
}

void	move_right(t_cub3d *data)
{
	data->map.player.pix_x += data->ray_c.dir_y * 1 * 3;
	data->map.player.pix_y += data->ray_c.dir_x * 1 * 3;
	data->map.offsetx += data->ray_c.dir_y * 1 * 3;
	data->map.offsety += data->ray_c.dir_x * 1 * 3;
	if (data->map.offsetx < 0)
	{
		data->map.player.x -= 1;
		data->map.offsetx += 25;
	}
	if (data->map.offsetx > 24)
	{
		data->map.player.x += 1;
		data->map.offsetx -= 25;
	}
	if (data->map.offsety < 0)
	{
		data->map.player.y -= 1;
		data->map.offsety += 25;
	}
	if (data->map.offsety > 24)
	{
		data->map.player.y += 1;
		data->map.offsety -= 25;
	}
	fov_cast(data, &data->ray_c, data->map.p_angle);
}

void	move_backward(t_cub3d *data)
{
	data->map.offsety += data->ray_c.dir_y * 3;
	data->map.player.pix_y += data->ray_c.dir_y * 3;
	if (data->map.offsety < 0)
	{
		data->map.player.y -= 1;
		data->map.offsety += 25;
	}
	if (data->map.offsety > 24)
	{
		data->map.player.y += 1;
		data->map.offsety -= 25;
	}
	data->map.offsetx -= data->ray_c.dir_x * 3;
	data->map.player.pix_x -= data->ray_c.dir_x * 3;
	if (data->map.offsetx > 24)
	{
		data->map.player.x += 1;
		data->map.offsetx -= 25;
	}
	if (data->map.offsetx < 0)
	{
		data->map.player.x -= 1;
		data->map.offsetx += 25;
	}
	fov_cast(data, &data->ray_c, data->map.p_angle);
}

void	move_forward(t_cub3d *data)
{
	printf("pos x = %f dir x = %f\n", data->ray_c.pos_x, data->ray_c.dir_x);
	printf("pos y = %f dir y = %f\n", data->ray_c.pos_y, data->ray_c.dir_y);
	printf("movespeed = %f\n", data->movespeed);
	// double dirX = cos(degree_to_rad(data->map.p_angle));
	// double dirY = sin(degree_to_rad(data->map.p_angle));

	// printf("posx is %f dirX is %f \n", data->ray_c.pos_x, dirX);
	// printf("y is %i x is %i\n", (int)(data->ray_c.pos_x + dirX * 3), (int)(data->ray_c.pos_y));
	if (data->map.grid[(int)(data->ray_c.pos_y + data->ray_c.dir_y * data->movespeed)][(int)(data->ray_c.pos_x)] == '0')
	{
		printf("here 1\n");
		data->ray_c.pos_y += data->ray_c.dir_y * data->movespeed;
	}
    if (data->map.grid[(int)(data->ray_c.pos_y)][(int)(data->ray_c.pos_x + data->ray_c.dir_x * data->movespeed)] == '0')
	{
		printf("here 2\n");
		data->ray_c.pos_x += data->ray_c.dir_x * data->movespeed;
		data->map.player.x += data->ray_c.dir_x * data->movespeed;
	}
	// data->map.offsety -= data->ray_c.dir_y * 3;
	// data->map.player.pix_y -= data->ray_c.dir_y * 3;
	// if (data->map.offsety < 0)
	// {
	// 	data->map.player.y -= 1;
	// 	data->map.offsety += 25;
	// }
	// if (data->map.offsety > 24)
	// {
	// 	data->map.player.y += 1;
	// 	data->map.offsety -= 25;
	// }
	// data->map.offsetx += data->ray_c.dir_x * 3;
	// data->map.player.pix_x += data->ray_c.dir_x * 3;
	// if (data->map.offsetx < 0)
	// {
	// 	data->map.player.x -= 1;
	// 	data->map.offsetx += 25;
	// }
	// if (data->map.offsetx > 24)
	// {
	// 	data->map.player.x += 1;
	// 	data->map.offsetx -= 25;
	// }
	draw_background(data);
	fov_cast(data, &data->ray_c, data->map.p_angle);
}

size_t	get_ms()
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	my_keyhook(mlx_key_data_t keydata, void *game_data)
{
	t_cub3d	*data;

	data = (t_cub3d *)game_data;
	// data->time = get_ms();
	data->old_time = data->time;
	data->time = get_ms();
	printf("time = %f old_time = %f\n", data->time, data->old_time);
	data->frametime = (data->time - data->old_time) / 1000.0;
	printf("frametime = %f\n", data->frametime);
	printf("FPS counter = %f\n", 1.0 / data->frametime);
	data->movespeed = data->frametime * 3.0;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_right(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_left(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_forward(data);
		// move(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_left(data);
		// move(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_right(data);
		// move(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_backward(data);
		// move(data);
}
