/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:25:41 by amakela           #+#    #+#             */
/*   Updated: 2024/09/12 14:19:55 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	validate_index(t_cub *data, char **layout, int y, int x)
{
	if (y == 0 || y == data->map.height - 1
		|| x == 0 || x == (int)ft_strlen(layout[y]) - 1)
		return (err("map must be surrounded by walls", NULL));
	if (ft_strchr("NSWE", layout[y][x]))
	{
		if (data->map.orientation)
			return (err("multiple starting positions found in the map", NULL));
		data->map.orientation = layout[y][x];
		data->map.player.x = x;
		data->map.player.y = y;
		return (0);
	}
	if (!ft_strchr("01NSWE", layout[y][x - 1])
		|| !ft_strchr("01NSWE", layout[y][x + 1])
		|| (int)ft_strlen(layout[y - 1]) < (x + 1)
		|| !ft_strchr("01NSWE", layout[y - 1][x])
		|| (int)ft_strlen(layout[y + 1]) < (x + 1)
		|| !ft_strchr("01NSWE", layout[y + 1][x]))
		return (err("map must be surrounded by walls", NULL));
	return (0);
}

int	validate_map(t_cub *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < data->map.height)
	{
		while (data->map.layout[y][x])
		{
			if (ft_strchr("0NSWE", data->map.layout[y][x]))
			{
				if (validate_index(data, data->map.layout, y, x))
					return (1);
			}
			x++;
		}
		y++;
		x = 0;
	}
	if (!data->map.orientation)
		return (err("no starting position found in the map", NULL));
	return (0);
}

int	copy_map(t_cub *data, int fd, char *file)
{
	int		i;
	char	*line;
	
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (err("open failed", NULL));
	data->map.layout = malloc((sizeof(char *) * data->map.height + 1));
	if (!data->map.layout)
		return (err("malloc failed", NULL));
	line = get_next_line(fd); // malloc/open check
	while (line)
	{
		if (ft_strchr("1 ", *line))
		{	
			if (line[ft_strlen(line) - 1] == '\n')
				data->map.layout[i++] = ft_substr(line, 0, ft_strlen(line) - 1);
			else
				data->map.layout[i++] = ft_substr(line, 0, ft_strlen(line));
			if (!data->map.layout[i - 1])
			{
				close (fd);
				return (err("malloc failed", line));
			}
		}
		free(line);
		line = get_next_line(fd); // malloc/open check
	}
	data->map.layout[i] = NULL;
	close(fd);
	return (0);
}

int	parse_map(t_cub *data, char *line, int fd, char *file)
{
	if (get_map_height(data, line, fd))
		return (1);
	if (copy_map(data, fd, file))
		return (1);
	get_map_width(data);
	if (validate_map(data))
		return (1);
	return (0);
}
