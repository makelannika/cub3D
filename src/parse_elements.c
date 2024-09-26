/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:25:51 by amakela           #+#    #+#             */
/*   Updated: 2024/09/26 21:37:37 by amakela          ###   ########.fr       */
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

int	check_identifier(char **element, t_cub3d *data)
{
	if (!ft_strncmp("F", element[0], 2))
		return (copy_color(data, element[1], 'F'));
	else if (!ft_strncmp("C", element[0], 2))
		return (copy_color(data, element[1], 'C'));
	if (!ft_strncmp("NO", element[0], 3))
		data->no_txtr = mlx_load_png(element[1]);
	else if (!ft_strncmp("SO", element[0], 3))
		data->so_txtr = mlx_load_png(element[1]);
	else if (!ft_strncmp("WE", element[0], 3))
		data->we_txtr = mlx_load_png(element[1]);
	else if (!ft_strncmp("EA", element[0], 3))
		data->ea_txtr = mlx_load_png(element[1]);
	else
		return (err("invalid .cub file content", NULL));
	if (mlx_errno)
		return (err("loading png failed", NULL));
	return (0);
}

int	parse_element(t_cub3d *data, char *line)
{
	char	**element;
	int		len;

	element = ft_split(line, ' ');
	if (!element)
		return (err("malloc failed", NULL));
	if (element[2])
	{
		free_str_array(element);
		return (err("invalid .cub file content", NULL));
	}
	len = ft_strlen(element[1]);
	element[1][len - 1] = '\0';
	if (check_identifier(element, data))
		return (free_str_array(element));
	free_str_array(element);
	data->elements_found++;
	return (0);
}

int	parse_file(t_cub3d *data, char *file)
{
	char	*line;

	data->fd = open(file, O_RDONLY);
	if (data->fd == -1)
		return (err("open failed", NULL));
	line = get_next_line(data->fd, &data->gnl_err);
	if (data->gnl_err)
		return (err("get_next_line failed", NULL));
	while (line && *line != '1' && *line != ' ')
	{
		if (*line != '\n')
		{
			if (parse_element(data, line))
				return (err(NULL, line));
		}
		free(line);
		line = get_next_line(data->fd, &data->gnl_err);
		if (data->gnl_err)
			return (err("get_next_line failed", NULL));
	}
	if (line && data->elements_found == 6)
		return (parse_map(data, line, file));
	else
		return (err("required elements not found in .cub file", line));
}
