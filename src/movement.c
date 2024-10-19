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
	if (data->map.grid[(int)(data->ray_c.pos_y + data->ray_c.dir_x * (data->mlx->delta_time * 3.0))]
		[(int)(data->ray_c.pos_x - data->ray_c.dir_y * (data->mlx->delta_time * 3.0))] != '1')
	{
		data->ray_c.pos_x -= data->ray_c.dir_y * (data->mlx->delta_time * 3.0);
		data->ray_c.pos_y += data->ray_c.dir_x * (data->mlx->delta_time * 3.0);
	}
	fov_cast(data, &data->ray_c);
}

void	move_right(t_cub3d *data)
{
	if (data->map.grid[(int)(data->ray_c.pos_y - data->ray_c.dir_x * (data->mlx->delta_time * 3.0))]
		[(int)(data->ray_c.pos_x + data->ray_c.dir_y * (data->mlx->delta_time * 3.0))] != '1')
	{
		data->ray_c.pos_x += data->ray_c.dir_y * (data->mlx->delta_time * 3.0);
		data->ray_c.pos_y -= data->ray_c.dir_x * (data->mlx->delta_time * 3.0);
	}
	fov_cast(data, &data->ray_c);
}

void	move_backward(t_cub3d *data)
{
	if (data->map.grid[(int)(data->ray_c.pos_y - data->ray_c.dir_y * (data->mlx->delta_time * 3.0))][(int)(data->ray_c.pos_x)] != '1')
		data->ray_c.pos_y -= data->ray_c.dir_y * (data->mlx->delta_time * 3.0);
	if (data->map.grid[(int)(data->ray_c.pos_y)][(int)(data->ray_c.pos_x - data->ray_c.dir_x * (data->mlx->delta_time * 3.0))] != '1')
		data->ray_c.pos_x -= data->ray_c.dir_x * (data->mlx->delta_time * 3.0);
	fov_cast(data, &data->ray_c);
}

void	move_forward(t_cub3d *data)
{
	if (data->map.grid[(int)(data->ray_c.pos_y + data->ray_c.dir_y * (data->mlx->delta_time * 3.0))][(int)(data->ray_c.pos_x)] != '1')
		data->ray_c.pos_y += data->ray_c.dir_y * (data->mlx->delta_time * 3.0);
	if (data->map.grid[(int)(data->ray_c.pos_y)][(int)(data->ray_c.pos_x + data->ray_c.dir_x * (data->mlx->delta_time * 3.0))] != '1')
		data->ray_c.pos_x += data->ray_c.dir_x * (data->mlx->delta_time * 3.0);
	fov_cast(data, &data->ray_c);
}

void	my_keyhook(void *game_data)
{
	t_cub3d	*data;

	data = (t_cub3d *)game_data;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
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
