/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:48:24 by linhnguy          #+#    #+#             */
/*   Updated: 2024/09/05 18:14:19 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	data;

	data = (t_cub){0};
	if (argc != 2 || check_extension(argv[1]))
		return (err("program takes one .cub file as an argument", NULL));
	if (parse_file(&data, argv[1]))
		return (free_data(&data));
	// ft_printf(1, "NO: %s\n", data.no);
	// ft_printf(1, "SO: %s\n", data.so);
	// ft_printf(1, "WE: %s\n", data.we);
	// ft_printf(1, "EA: %s\n", data.ea);
	// ft_printf(1, "floor: %d,%d,%d\n", data.floor[0], data.floor[1], data.floor[2]);
	// ft_printf(1, "ceiling: %d,%d,%d\n", data.ceiling[0], data.ceiling[1], data.ceiling[2]);
	// ft_printf(1, "map height: %d\n", data.map.height);
	// ft_printf(1, "map width: %d\n", data.map.width);
	// for (int i = 0; i < data.map.height; i++)
	// 	ft_printf(1, "%s\n", data.map.layout[i]);
	// ft_printf(1, "player x: %d y: %d\n", data.map.player.x, data.map.player.y);
	do_game(data);
	free_data(&data);
	return (0);
}
