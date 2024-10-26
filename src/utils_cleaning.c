/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleaning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:27:06 by amakela           #+#    #+#             */
/*   Updated: 2024/10/26 15:29:54 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	err(char *str, char *ptr)
{
	printf("in err freeing: %s\n", ptr);
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
	if (data->north)
	{
		printf("deleting north\n");
		mlx_delete_texture(data->north);
	}
	if (data->south)
	{
		printf("deleting south\n");
		mlx_delete_texture(data->south);
	}
	if (data->west)
	{
		printf("deleting west\n");
		mlx_delete_texture(data->west);
	}
	if (data->east)
	{
		printf("deleting east\n");
		mlx_delete_texture(data->east);
	}
	if (data->map.grid)
	{
		printf("freeing grid\n");
		free_str_array(data->map.grid);
	}
	if (data->mlx)
	{
		printf("terminating mlx\n");
		mlx_terminate(data->mlx);
	}
	if (data->fd > 0)
	{
		printf("closing fd\n");
		close(data->fd);
	}
	return (1);
}
