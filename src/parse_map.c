/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:25:41 by amakela           #+#    #+#             */
/*   Updated: 2024/09/27 16:35:09 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	validate_map(t_cub3d *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < data->map.height)
	{
		while (data->map.grid[y][x])
		{
			if (ft_strchr("0NSWE", data->map.grid[y][x]))
			{
				if (validate_index(data, data->map.grid, y, x))
					return (1);
			}
			x++;
		}
		y++;
		x = 0;
	}
	if (!data->map.player.pix_x)
		return (err("no starting position found in the map", NULL));
	return (0);
}

void	get_map_width(t_cub3d *data)
{
	int	i;

	i = 0;
	while (data->map.grid[i])
	{
		if ((int)ft_strlen(data->map.grid[i]) > data->map.width)
			data->map.width = ft_strlen(data->map.grid[i]);
		i++;
	}
}

int	copy_map(t_cub3d *data)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(data->fd, &data->gnl_err);
	if (data->gnl_err)
		return (err("get_next_line failed", NULL));
	while (line)
	{
		if (ft_strchr("1 ", *line))
		{	
			if (line[ft_strlen(line) - 1] == '\n')
				data->map.grid[i++] = ft_substr(line, 0, ft_strlen(line) - 1);
			else
				data->map.grid[i++] = ft_substr(line, 0, ft_strlen(line));
			if (!data->map.grid[i - 1])
				return (err("malloc failed", line));
		}
		free(line);
		line = get_next_line(data->fd, &data->gnl_err);
		if (data->gnl_err)
			return (err("4 get_next_line failed", NULL));
	}
	return (0);
}

int	get_map_height(t_cub3d *data, char *line)
{
	while (line && ft_strchr("1 ", *line))
	{
		if (validate_line(line))
			return (err("forbidden character found in the map", line));
		data->map.height++;
		free(line);
		line = get_next_line(data->fd, &data->gnl_err);
		if (data->gnl_err)
			return (err("get_next_line failed", NULL));
	}
	if (line)
		return (err("invalid .cub file content", line));
	close(data->fd);
	return (0);
}

int	parse_map(t_cub3d *data, char *line, char *file)
{
	if (get_map_height(data, line))
		return (1);
	if (create_grid(data, file))
		return (1);
	if (copy_map(data))
		return (1);
	get_map_width(data);
	if (validate_map(data))
		return (1);
	return (0);
}
