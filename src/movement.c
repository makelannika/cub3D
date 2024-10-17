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
	
	// data->map.player.pix_x += data->ray_c.dir_y * 1 * 3;
	// data->map.player.pix_y += data->ray_c.dir_x * 1 * 3;
	// data->map.offsetx += data->ray_c.dir_y * 1 * 3;
	// data->map.offsety += data->ray_c.dir_x * 1 * 3;
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
	fov_cast(data, &data->ray_c, data->map.p_angle);
}

void	move_backward(t_cub3d *data)
{
	if (data->map.grid[(int)(data->ray_c.pos_y - data->ray_c.ray_dir_y * (data->mlx->delta_time * 5))][(int)(data->ray_c.pos_x)] != '1')
		data->ray_c.pos_y -= data->ray_c.ray_dir_y * (data->mlx->delta_time * 5);
    if (data->map.grid[(int)(data->ray_c.pos_y)][(int)(data->ray_c.pos_x - data->ray_c.dir_x * (data->mlx->delta_time * 5))] != '1')
		data->ray_c.pos_x -= data->ray_c.dir_x * (data->mlx->delta_time * 5);
	fov_cast(data, &data->ray_c, data->map.p_angle);
	// data->map.offsety += data->ray_c.dir_y * 3;
	// data->map.player.pix_y += data->ray_c.dir_y data->ray_c.dir_y
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
	// data->map.offsetx -= data->ray_c.dir_x * 3;
	// data->map.player.pix_x -= data->ray_c.dir_x * 3;
	// if (data->map.offsetx > 24)
	// {
	// 	data->map.player.x += 1;
	// 	data->map.offsetx -= 25;
	// }
	// if (data->map.offsetx < 0)
	// {
	// 	data->map.player.x -= 1;
	// 	data->map.offsetx += 25;
	// }
}

void	move_forward(t_cub3d *data)
{
	if (data->map.grid[(int)(data->ray_c.pos_y + data->ray_c.dir_y * (data->mlx->delta_time * 5.0))][(int)(data->ray_c.pos_x)] != '1')
		data->ray_c.pos_y += data->ray_c.dir_y * (data->mlx->delta_time * 5);
    if (data->map.grid[(int)(data->ray_c.pos_y)][(int)(data->ray_c.pos_x + data->ray_c.dir_x * (data->mlx->delta_time * 5.0))] != '1')
		data->ray_c.pos_x += data->ray_c.dir_x * (data->mlx->delta_time * 5);
	// printf("first y is %i x is %i\n", (int)(data->ray_c.pos_x + data->ray_c.ray_dir_x * (data->mlx->delta_time * 3)), (int)(data->ray_c.pos_y));
	// if (data->map.grid[(int)(data->ray_c.pos_x + data->ray_c.ray_dir_x * (data->mlx->delta_time * 3))][(int)(data->ray_c.pos_y)] == '0')
	// {
	// 	printf("here\n");
	// 	data->ray_c.pos_x += data->ray_c.ray_dir_x * (data->mlx->delta_time * 3);
	// }
	// printf("second y is %i x is %i\n", (int)(data->ray_c.pos_x), (int)(data->ray_c.pos_y + data->ray_c.ray_dir_y * (data->mlx->delta_time * 3)));
    // if (data->map.grid[(int)(data->ray_c.pos_x)][(int)(data->ray_c.pos_y + data->ray_c.ray_dir_y * (data->mlx->delta_time * 3))] == '0')
	// {
	// 	printf("here2\n");
	// 	data->ray_c.pos_y += data->ray_c.ray_dir_y * (data->mlx->delta_time * 3);
	// }
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
	fov_cast(data, &data->ray_c, data->map.p_angle);
}

void	my_keyhook(mlx_key_data_t keydata, void *game_data)
{
	t_cub3d	*data;
	
	data = (t_cub3d *)game_data;
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
