/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleaning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:27:06 by amakela           #+#    #+#             */
/*   Updated: 2024/09/19 15:10:07 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	err(char *str, void *ptr)
{
	if (str)
		ft_printf(2, "Error: %s\n", str);
	if (ptr)
		free(ptr);
	return (1);
}

int	free_str_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (1);
}

int	free_data(t_cub3d *data)
{
	if (data->no_txtr)
		mlx_delete_texture(data->no_txtr);
	if (data->so_txtr)
		mlx_delete_texture(data->so_txtr);
	if (data->we_txtr)
		mlx_delete_texture(data->we_txtr);
	if (data->ea_txtr)
		mlx_delete_texture(data->ea_txtr);
	if (data->map.grid)
		free_str_array(data->map.grid);
	return (1);
}

