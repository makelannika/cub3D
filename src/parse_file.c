/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:13:04 by amakela           #+#    #+#             */
/*   Updated: 2024/11/05 14:42:45 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	elements_found(t_cub3d *data)
{
	if (data->north && data->south && data->west && data->east
		&& data->floor[0] && data->ceiling[0])
		return (1);
	return (0);
}

int	check_identifier(char **element, t_cub3d *data)
{
	if (!ft_strncmp("F", element[0], 2) && !data->floor[0])
		return (copy_color(data, element[1], 'F'));
	if (!ft_strncmp("C", element[0], 2) && !data->ceiling[0])
		return (copy_color(data, element[1], 'C'));
	if (!ft_strncmp("NO", element[0], 3) && !data->north)
		data->north = mlx_load_png(element[1]);
	else if (!ft_strncmp("SO", element[0], 3) && !data->south)
		data->south = mlx_load_png(element[1]);
	else if (!ft_strncmp("WE", element[0], 3) && !data->west)
		data->west = mlx_load_png(element[1]);
	else if (!ft_strncmp("EA", element[0], 3) && !data->east)
		data->east = mlx_load_png(element[1]);
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

	if (*line == ' ')
		return (err("invalid .cub file content", NULL));
	element = ft_split(line, ' ');
	if (!element)
		return (err("malloc failed", NULL));
	if (get_arr_len(element) != 2)
	{
		free_str_array(element);
		return (err("invalid .cub file content", NULL));
	}
	len = ft_strlen(element[1]);
	element[1][len - 1] = '\0';
	if (check_identifier(element, data))
		return (free_str_array(element));
	free_str_array(element);
	return (0);
}

int	parse_file(t_cub3d *data, t_gnl *gnl, char *file)
{
	char	*line;

	gnl->fd = open(file, O_RDONLY);
	if (gnl->fd == -1)
		return (err("open failed", NULL));
	line = get_next_line(gnl);
	if (gnl->err)
		return (err("get_next_line failed", NULL));
	while (line && (!elements_found(data) || *line == '\n'))
	{
		if (*line != '\n')
		{
			if (parse_element(data, line))
				return (err(NULL, line));
		}
		free(line);
		line = get_next_line(gnl);
		if (gnl->err)
			return (err("get_next_line failed", NULL));
	}
	if (line)
		return (parse_map(data, gnl, line, file));
	else
		return (err("required elements not found in .cub file", line));
}
