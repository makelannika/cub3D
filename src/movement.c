/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:45:22 by amakela           #+#    #+#             */
/*   Updated: 2024/10/24 22:40:50 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_right(t_cub3d *data, t_ray *ray_c)
{
	int		new_x;
	int		new_y;
	float	frame;
	float	limit;

	limit = .12;
	frame = .08;
	new_x = ray_c->pos_x - ray_c->dir_y * limit;
	new_y = ray_c->pos_y + ray_c->dir_x * limit;
	if (data->map.grid[new_y][(int)(ray_c->pos_x)] != '1')
		ray_c->pos_y += ray_c->dir_x * frame;
	if (data->map.grid[(int)(ray_c->pos_y)][new_x] != '1')
		ray_c->pos_x -= ray_c->dir_y * frame;
	fov_cast(data, ray_c);
}

void	move_left(t_cub3d *data, t_ray *ray_c)
{
	int		new_x;
	int		new_y;
	float	frame;
	float	limit;

	limit = .12;
	frame = .08;
	new_x = ray_c->pos_x + ray_c->dir_y * limit;
	new_y = ray_c->pos_y - ray_c->dir_x * limit;
	if (data->map.grid[new_y][(int)(ray_c->pos_x)] != '1')
		ray_c->pos_y -= ray_c->dir_x * frame;
	if (data->map.grid[(int)(ray_c->pos_y)][new_x] != '1')
		ray_c->pos_x += ray_c->dir_y * frame;
	fov_cast(data, ray_c);
}

void	move_backward(t_cub3d *data, t_ray *ray_c)
{
	int		new_x;
	int		new_y;
	float	frame;
	float	limit;

	limit = .12;
	frame = .08;
	new_x = data->ray_c.pos_x - data->ray_c.dir_x * limit;
	new_y = data->ray_c.pos_y - data->ray_c.dir_y * limit;
	if (data->map.grid[new_y][(int)(data->ray_c.pos_x)] != '1')
		data->ray_c.pos_y -= data->ray_c.dir_y * frame;
	if (data->map.grid[(int)(data->ray_c.pos_y)][new_x] != '1')
		data->ray_c.pos_x -= data->ray_c.dir_x * frame;
	fov_cast(data, ray_c);
}

void	move_forward(t_cub3d *data, t_ray *ray_c)
{
	int		new_x;
	int		new_y;
	float	frame;
	float	limit;

	limit = .12;
	frame = .08;
	new_x = ray_c->pos_x + ray_c->dir_x * limit;
	new_y = ray_c->pos_y + ray_c->dir_y * limit;
	if (data->map.grid[new_y][(int)(ray_c->pos_x)] != '1')
		ray_c->pos_y += ray_c->dir_y * frame;
	if (data->map.grid[(int)(ray_c->pos_y)][new_x] != '1')
		ray_c->pos_x += ray_c->dir_x * frame;
	fov_cast(data, ray_c);
}

void	my_keyhook(void *game_data)
{
	t_cub3d	*data;

	data = (t_cub3d *)game_data;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_right(data, &data->ray_c);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_left(data, &data->ray_c);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_forward(data, &data->ray_c);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_left(data, &data->ray_c);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_right(data, &data->ray_c);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_backward(data, &data->ray_c);
}
