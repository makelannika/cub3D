/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:25:51 by amakela           #+#    #+#             */
/*   Updated: 2024/09/19 15:10:37 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	validate_color(char *str)
{
	int	i;
	int	color;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9'))
			return (err("invalid .cub file content", NULL));
		i++;
	}
	color = ft_atoi(str);
	if (color < 0 || color > 255)
		return (err("invalid .cub file content", NULL));
	return (color);
}

int	copy_color(char *str, int *id)
{
	char	**rgb;

	if (count_commas(str) != 2)
		return (err("invalid .cub file content", NULL));
	rgb = ft_split(str, ',');
	if (!rgb)
		return (err("malloc failed", NULL));
	id[0] = validate_color(rgb[0]);
	id[1] = validate_color(rgb[1]);
	id[2] = validate_color(rgb[2]);
	if (id[0] == -1 || id[1] == -1 || id[2] == -1)
		return (free_str_array(rgb));
	free_str_array(rgb);
	return (0);
}

int	check_identifier(char **element, t_cub3d *data)
{
	char	*copy;

	if (!ft_strncmp("F", element[0], 2))
		return (copy_color(element[1], data->floor));
	else if (!ft_strncmp("C", element[0], 2))
		return (copy_color(element[1], data->ceiling));
	copy = ft_strdup(element[1]);
	if (!copy)
		return (err("malloc failed", NULL));
	if (!ft_strncmp("NO", element[0], 3))
		data->no_txtr = mlx_load_png(copy);
	else if (!ft_strncmp("WE", element[0], 3))
		data->we_txtr = mlx_load_png(copy);
	else if (!ft_strncmp("EA", element[0], 3))
		data->ea_txtr = mlx_load_png(copy);
	else if (!ft_strncmp("SO", element[0], 3))
		data->so_txtr = mlx_load_png(copy);
	else
		return (err("invalid .cub file content", copy));
	if (mlx_errno)
		return (err("loading png failed", copy));
	free(copy);
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
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (err("open failed", NULL));
	line = get_next_line(fd);
	// if (errno)
	// 	return (err("1 get_next_line failed", NULL));
	while (line && *line != '1' && *line != ' ')
	{
		if (*line != '\n')
		{
			if (parse_element(data, line))
				return (err(NULL, line));
		}
		free(line);
		line = get_next_line(fd);
		// if (errno)
		// 	return (err("2 get_next_line failed", NULL));
	}
	if (line && ft_strchr(" 1", *line) && data->elements_found == 6)
		return (parse_map(data, line, fd, file));
	else
		return (err("required elements not found in .cub file", line));
}
