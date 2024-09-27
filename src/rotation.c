/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:48:37 by amakela           #+#    #+#             */
/*   Updated: 2024/09/27 19:30:26 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	rotate_right(t_cub3d *data)
{
	reset_minimap(data);
	draw_minimap(data, data->map.player.y - 5, data->map.player.x -5);
	data->map.p_angle -= 15;
	if (data->map.p_angle < 0)
		data->map.p_angle = 345;
	draw_player(data, data->map.p_angle);
}

void	rotate_left(t_cub3d *data)
{
	reset_minimap(data);
	draw_minimap(data, data->map.player.y - 5, data->map.player.x -5);
	data->map.p_angle += 15;
	if (data->map.p_angle > 360)
		data->map.p_angle = 15;
	draw_player(data, data->map.p_angle);
}
