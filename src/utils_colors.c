/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 15:55:39 by amakela           #+#    #+#             */
/*   Updated: 2024/10/25 14:37:32 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	rgba_to_hex(int r, int g, int b, int a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

int	get_color(char *str)
{
	int	color;

	color = ft_atoi(str);
	if (color < 0 || color > 255)
		return (-1);
	return (color);
}

int	validate_colors(char *str)
{
	int	commas;

	commas = 0;
	while (*str)
	{
		if ((*str < '0' || *str > '9') && *str != ',')
			return (1);
		if (*str == ',')
			commas++;
		str++;
	}
	if (commas != 2)
		return (1);
	return (0);
}

int	copy_color(t_cub3d *data, char *str, char identifier)
{
	char	**rgb;
	int		red;
	int		green;
	int		blue;

	if (validate_colors(str))
		return (err("invalid floor/ceiling color", NULL));
	rgb = ft_split(str, ',');
	if (!rgb)
		return (err("malloc failed", NULL));
	red = get_color(rgb[0]);
	green = get_color(rgb[1]);
	blue = get_color(rgb[2]);
	if (red == -1 || green == -1 || blue == -1)
	{
		free_str_array(rgb);
		return (err("invalid floor/ceiling color", NULL));
	}
	if (identifier == 'F')
		data->floor = rgba_to_hex(red, green, blue, 255);
	else
		data->ceiling = rgba_to_hex(red, green, blue, 255);
	free_str_array(rgb);
	return (0);
}
