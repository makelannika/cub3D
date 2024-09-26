/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:18:02 by linhnguy          #+#    #+#             */
/*   Updated: 2024/09/26 21:52:37 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void	get_wall_pixels(t_cub3d *data)
// {
// 	int 		i = 0;
// 	int			y = 0;
	
// 	uint8_t		*no = data->no_txtr->pixels;
// 	uint8_t		*so = data->so_txtr->pixels;
// 	uint8_t		*we = data->we_txtr->pixels;
// 	uint8_t		*ea = data->ea_txtr->pixels;

// 	while (y < 4000000)
// 	{
// 		data->north[i] = rgba_to_hex(no[y], no[y + 1], no[y + 2], no[y + 3]);
// 		data->south[i] = rgba_to_hex(so[y], so[y + 1], so[y + 2], so[y + 3]);
// 		data->west[i] = rgba_to_hex(we[y], we[y + 1], we[y + 2], we[y + 3]);
// 		data->east[i] = rgba_to_hex(ea[y], ea[y + 1], ea[y + 2], ea[y + 3]);
// 		i++;
// 		y += 4;
// 	}
// }

int	create_images(t_cub3d *data)
{
	data->minimap_txtr = mlx_load_png("assets/black_bg.png");
	if (!data->minimap_txtr)
		return (err("loading png failed", NULL));
	data->minimap = mlx_texture_to_image(data->mlx, data->minimap_txtr);
	data->background = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->minimap || !data->background)
		return (err("creating image failed", NULL));
	if (mlx_image_to_window(data->mlx, data->background, 0, 0) == -1)
		return (err("displaying image failed", NULL));
	if (mlx_image_to_window(data->mlx, data->minimap, 0, 0) == -1)
		return (err("displaying image failed", NULL));
	// data->north = (uint32_t *)data->no_txtr->pixels;
	// data->south = (uint32_t *)data->so_txtr->pixels;
	// data->west = (uint32_t *)data->we_txtr->pixels;
	// data->east = (uint32_t *)data->ea_txtr->pixels;
	// get_wall_pixels(data);
	return (0);
}

int	init_game(t_cub3d *data)
{
	data->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D", false);
	if (!data->mlx)
		return (err("initializing mlx failed", NULL));
	if (create_images(data))
		return (1);
	draw_player(data, data->map.p_angle);
	draw_minimap(data, data->map.player.y - 5, data->map.player.x -5);
	mlx_key_hook(data->mlx, &my_keyhook, data);
	mlx_loop(data->mlx);
	return (0);
}
