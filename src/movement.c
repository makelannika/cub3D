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
	double dirX = cos(degree_to_rad(data->map.p_angle));
	double dirY = sin(degree_to_rad(data->map.p_angle));

	if (data->map.grid[(int)(data->ray_c.pos_y + dirY * (data->mlx->delta_time * 3))][(int)(data->ray_c.pos_x)] == '0')
	{
		data->ray_c.pos_y += dirY * (data->mlx->delta_time * 3);
		printf("posy is %f\n", data->ray_c.pos_y);
	}
    if (data->map.grid[(int)(data->ray_c.pos_y)][(int)(data->ray_c.pos_x + dirX * (data->mlx->delta_time * 3))] == '0')
	{
		data->ray_c.pos_x += dirX * (data->mlx->delta_time * 3);
		printf("posx is %f\n", data->ray_c.pos_x);
	}

	// if (data->map.grid[(int)(data->ray_c.pos_x + dirX * (data->mlx->delta_time * 3))][(int)(data->ray_c.pos_y)] == '0')
	// 	data->ray_c.pos_x += dirX * (data->mlx->delta_time * 3);
    // if (data->map.grid[(int)(data->ray_c.pos_x)][(int)(data->ray_c.pos_y + dirY * (data->mlx->delta_time * 3))] == '0')
	// 	data->ray_c.pos_y += dirY * (data->mlx->delta_time * 3);
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

// void	get_time_difference(struct timeval *old_time, t_cub3d *data)
// {
// 	struct timeval current_time;
	
// 	gettimeofday(&current_time, NULL);
//     double start_time = old_time->tv_sec + (old_time->tv_usec / 1000000.0);
//     double end_time = current_time.tv_sec + (current_time.tv_usec / 1000000.0);
//     data->frame_time = end_time - start_time;
// 	old_time->tv_sec = current_time.tv_sec;
// 	old_time->tv_usec = current_time.tv_usec;
// }

void	my_keyhook(mlx_key_data_t keydata, void *game_data)
{
	t_cub3d	*data;
	
	data = (t_cub3d *)game_data;
	// get_time_difference(&data->old_time, data);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_right(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_left(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_forward(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_left(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_right(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_backward(data);
}
