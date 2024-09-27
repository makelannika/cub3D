/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:25:41 by amakela           #+#    #+#             */
/*   Updated: 2024/09/24 16:50:28 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_orientation(t_cub3d *data, char orientation, int x, int y)
{
	if (orientation == 'E')
		data->map.p_angle = 0.0;
	else if (orientation == 'N')
		data->map.p_angle = 90.0;
	else if (orientation == 'W')
		data->map.p_angle = 180.0;
	else if (orientation == 'S')
		data->map.p_angle = 270.0;
	data->map.player.x = x;
	data->map.player.y = y;
	data->map.offsetx = 13;
	data->map.offsety = 13;
	data->map.player.pix_x = x * 25 + 13;
	data->map.player.pix_y = y * 25 + 13;
}

int	validate_index(t_cub3d *data, char **grid, int y, int x)
{
	if (ft_strchr("NSWE", grid[y][x]))
	{
		if (data->map.player.pix_x)
			return (err("multiple starting positions found in the map", NULL));
		set_orientation(data, grid[y][x], x, y);
		return (0);
	}
	if (!grid[y][x - 1] || !ft_strchr("01NSWE", grid[y][x - 1])
		|| !grid[y][x + 1] || !ft_strchr("01NSWE", grid[y][x + 1])
		|| !grid[y - 1][x] || !ft_strchr("01NSWE", grid[y - 1][x])
		|| !grid[y + 1][x] || !ft_strchr("01NSWE", grid[y + 1][x]))
		return (err("map must be surrounded by walls", NULL));
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
	if (!data->map.player.pix_x)
		return (err("no starting position found in the map", NULL));
	return (0);
}

int	copy_map(t_cub3d *data, char *file)
{
	int		i;
	char	*line;

	i = 0;
	data->fd = open(file, O_RDONLY);
	if (data->fd == -1)
		return (err("open failed", NULL));
	data->map.grid = ft_calloc(data->map.height + 1, sizeof(char *));
	if (!data->map.grid)
		return (err("malloc failed", NULL));
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

int	parse_map(t_cub3d *data, char *line, char *file)
{
	if (get_map_height(data, line))
		return (1);
	if (copy_map(data, file))
		return (1);
	get_map_width(data);
	if (validate_map(data))
		return (1);
	return (0);
}
