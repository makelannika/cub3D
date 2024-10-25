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

void	move_right(t_cub3d *data, t_ray *ray)
{
	int		new_x;
	int		new_y;
	float	frame;
	float	limit;

	limit = .12;
	frame = .06;
	new_x = ray->pos_x - ray->dir_y * limit;
	new_y = ray->pos_y + ray->dir_x * limit;
	if (data->map.grid[new_y][(int)(ray->pos_x)] != '1')
		ray->pos_y += ray->dir_x * frame;
	if (data->map.grid[(int)(ray->pos_y)][new_x] != '1')
		ray->pos_x -= ray->dir_y * frame;
	fov_cast(data, ray);
}

void	move_left(t_cub3d *data, t_ray *ray)
{
	int		new_x;
	int		new_y;
	float	frame;
	float	limit;

	limit = .12;
	frame = .06;
	new_x = ray->pos_x + ray->dir_y * limit;
	new_y = ray->pos_y - ray->dir_x * limit;
	if (data->map.grid[new_y][(int)(ray->pos_x)] != '1')
		ray->pos_y -= ray->dir_x * frame;
	if (data->map.grid[(int)(ray->pos_y)][new_x] != '1')
		ray->pos_x += ray->dir_y * frame;
	fov_cast(data, ray);
}

void	move_backward(t_cub3d *data, t_ray *ray)
{
	int		new_x;
	int		new_y;
	float	frame;
	float	limit;

	limit = .12;
	frame = .06;
	new_x = data->ray.pos_x - data->ray.dir_x * limit;
	new_y = data->ray.pos_y - data->ray.dir_y * limit;
	if (data->map.grid[new_y][(int)(data->ray.pos_x)] != '1')
		data->ray.pos_y -= data->ray.dir_y * frame;
	if (data->map.grid[(int)(data->ray.pos_y)][new_x] != '1')
		data->ray.pos_x -= data->ray.dir_x * frame;
	fov_cast(data, ray);
}

void	move_forward(t_cub3d *data, t_ray *ray)
{
	int		new_x;
	int		new_y;
	float	frame;
	float	limit;

	limit = .12;
	frame = .06;
	new_x = ray->pos_x + ray->dir_x * limit;
	new_y = ray->pos_y + ray->dir_y * limit;
	if (data->map.grid[new_y][(int)(ray->pos_x)] != '1')
		ray->pos_y += ray->dir_y * frame;
	if (data->map.grid[(int)(ray->pos_y)][new_x] != '1')
		ray->pos_x += ray->dir_x * frame;
	fov_cast(data, ray);
}

void	my_keyhook(void *game_data)
{
	t_cub3d	*data;

	data = (t_cub3d *)game_data;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_right(data, &data->ray);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_left(data, &data->ray);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_forward(data, &data->ray);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_left(data, &data->ray);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_right(data, &data->ray);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_backward(data, &data->ray);
}
