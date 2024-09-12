/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:25:41 by amakela           #+#    #+#             */
/*   Updated: 2024/09/12 17:11:25 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_orientation(t_cub3d *data, char orientation)
{
	if (orientation == 'E')
		data->map.p_angle = 0.0;
	else if (orientation == 'N')
		data->map.p_angle = 90.0;
	else if (orientation == 'W')
		data->map.p_angle = 180.0;
	else if (orientation == 'S')
		data->map.p_angle = 270.0;
	data->map.offsetx = 13;
	data->map.offsety = 13;
}

int	validate_index(t_cub3d *data, char **map, int y, int x)
{
	if (y == 0 || y == data->map.map_height - 1
		|| x == 0 || x == (int)ft_strlen(map[y]) - 1)
		return (err("map must be surrounded by walls", NULL));
	if (ft_strchr("NSWE", map[y][x]))
	{
		if (data->map.orientation)
			return (err("multiple starting positions found in the map", NULL));
		set_orientation(data, map[y][x]);
		data->map.orientation = map[y][x];
		data->map.player.x = x;
		data->map.player.y = y;
		return (0);
	}
	if (!ft_strchr("01NSWE", map[y][x - 1])
		|| !ft_strchr("01NSWE", map[y][x + 1])
		|| (int)ft_strlen(map[y - 1]) < (x + 1)
		|| !ft_strchr("01NSWE", map[y - 1][x])
		|| (int)ft_strlen(map[y + 1]) < (x + 1)
		|| !ft_strchr("01NSWE", map[y + 1][x]))
		return (err("map must be surrounded by walls", NULL));
	return (0);
}

int	validate_map(t_cub3d *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < data->map.map_height)
	{
		while (data->map.map[y][x])
		{
			if (ft_strchr("0NSWE", data->map.map[y][x]))
			{
				if (validate_index(data, data->map.map, y, x))
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

int	copy_map(t_cub3d *data, int fd, char *file)
{
	int		i;
	char	*line;
	
	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (err("open failed", NULL));
	data->map.map = malloc((sizeof(char *) * data->map.map_height + 1));
	if (!data->map.map)
		return (err("malloc failed", NULL));
	line = get_next_line(fd); // malloc/open check
	while (line)
	{
		if (ft_strchr("1 ", *line))
		{	
			if (line[ft_strlen(line) - 1] == '\n')
				data->map.map[i++] = ft_substr(line, 0, ft_strlen(line) - 1);
			else
				data->map.map[i++] = ft_substr(line, 0, ft_strlen(line));
			if (!data->map.map[i - 1])
			{
				close (fd);
				return (err("malloc failed", line));
			}
		}
		free(line);
		line = get_next_line(fd); // malloc/open check
	}
	data->map.map[i] = NULL;
	close(fd);
	return (0);
}

int	parse_map(t_cub3d *data, char *line, int fd, char *file)
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
