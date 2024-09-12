/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cleaning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:27:06 by amakela           #+#    #+#             */
/*   Updated: 2024/09/12 16:45:37 by amakela          ###   ########.fr       */
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
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
	if (data->map.map)
		free_str_array(data->map.map);
	return (1);
}
