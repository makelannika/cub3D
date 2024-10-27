/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:33:08 by amakela           #+#    #+#             */
/*   Updated: 2024/10/27 18:53:59 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_arr_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	set_orientation(t_cub3d *data, char orientation)
{
	if (orientation == 'E')
	{
		data->ray.plane_x = 0.0;
		data->ray.plane_y = -0.66;
		data->map.angle = 0.0;
	}
	else if (orientation == 'S')
	{
		data->ray.plane_x = 0.66;
		data->ray.plane_y = 0.0;
		data->map.angle = 90.0;
	}
	else if (orientation == 'W')
	{
		data->ray.plane_x = 0.0;
		data->ray.plane_y = 0.66;
		data->map.angle = 180.0;
	}
	else if (orientation == 'N')
	{
		data->ray.plane_x = -0.66;
		data->ray.plane_y = 0.0;
		data->map.angle = 270.0;
	}
}

int	validate_line(char *str)
{
	while (*str)
	{
		if (!ft_strchr(" 10NSWE\n", *str))
			return (1);
		str++;
	}
	return (0);
}

int	create_grid(t_cub3d *data, char *file)
{
	data->gnl.fd = open(file, O_RDONLY);
	if (data->gnl.fd == -1)
		return (err("open failed", NULL));
	data->map.grid = ft_calloc(data->map.height + 1, sizeof(char *));
	if (!data->map.grid)
		return (err("malloc failed", NULL));
	return (0);
}

int	check_extension(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len > 4)
		return (ft_strncmp(&arg[len - 4], ".cub", 5));
	return (1);
}
