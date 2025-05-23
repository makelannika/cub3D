/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleaning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:27:06 by amakela           #+#    #+#             */
/*   Updated: 2024/10/29 18:39:22 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	err(char *str, char *ptr)
{
	if (str)
		ft_printf(2, "Error\n%s\n", str);
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
	if (data->gnl.text_read)
		free(data->gnl.text_read);
	if (data->north)
		mlx_delete_texture(data->north);
	if (data->south)
		mlx_delete_texture(data->south);
	if (data->west)
		mlx_delete_texture(data->west);
	if (data->east)
		mlx_delete_texture(data->east);
	if (data->map.grid)
		free_str_array(data->map.grid);
	if (data->mlx)
		mlx_terminate(data->mlx);
	if (data->gnl.fd > 0)
		close(data->gnl.fd);
	return (1);
}
