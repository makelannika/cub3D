/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:25:41 by amakela           #+#    #+#             */
/*   Updated: 2024/10/28 15:46:46 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	validate_index(t_cub3d *data, char **grid, int y, int x)
{
	if (y == 0 || x == 0 || y == data->map.height - 1
		|| x == (int)ft_strlen(grid[y]) - 1
		|| x >= (int)ft_strlen(grid[y + 1])
		|| x >= (int)ft_strlen(grid[y - 1])
		|| !ft_strchr("01NSWE", grid[y][x - 1])
		|| !ft_strchr("01NSWE", grid[y][x + 1])
		|| !ft_strchr("01NSWE", grid[y - 1][x])
		|| !ft_strchr("01NSWE", grid[y + 1][x]))
		return (err("map must be surrounded by walls", NULL));
	if (ft_strchr("NSWE", grid[y][x]))
	{
		if (data->map.x)
			return (err("multiple starting positions found in the map", NULL));
		set_orientation(data, grid[y][x]);
		data->map.x = x;
		data->map.y = y;
	}
	return (0);
}

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
	if (!data->map.x)
		return (err("no starting position found in the map", NULL));
	return (0);
}

int	copy_map(t_cub3d *data, t_gnl *gnl)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(gnl);
	if (gnl->err)
		return (err("get_next_line failed", NULL));
	while (line)
	{
		if (!validate_line(line))
		{
			if (line[ft_strlen(line) - 1] == '\n')
				data->map.grid[i++] = ft_substr(line, 0, ft_strlen(line) - 1);
			else
				data->map.grid[i++] = ft_substr(line, 0, ft_strlen(line));
			if (!data->map.grid[i - 1])
				return (err("malloc failed", line));
		}
		free(line);
		line = get_next_line(gnl);
		if (gnl->err)
			return (err("get_next_line failed", NULL));
	}
	return (0);
}

int	get_map_height(t_cub3d *data, t_gnl *gnl, char *line)
{
	while (line && !validate_line(line))
	{
		data->map.height++;
		free(line);
		line = get_next_line(gnl);
		if (gnl->err)
			return (err("get_next_line failed", NULL));
	}
	if (line)
		return (err("invalid map content", line));
	if (gnl->text_read)
		free(gnl->text_read);
	close(gnl->fd);
	return (0);
}

int	parse_map(t_cub3d *data, t_gnl *gnl, char *line, char *file)
{
	if (get_map_height(data, gnl, line))
		return (1);
	data->map.grid = ft_calloc(data->map.height + 1, sizeof(char *));
	if (!data->map.grid)
		return (err("malloc failed", NULL));
	data->gnl.fd = open(file, O_RDONLY);
	if (data->gnl.fd == -1)
		return (err("open failed", NULL));
	if (copy_map(data, gnl) || validate_map(data))
		return (1);
	return (0);
}
