/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:48:24 by linhnguy          #+#    #+#             */
/*   Updated: 2024/09/03 21:03:17 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_extension(char *arg)
{
	int     len;

	len = ft_strlen(arg);
	return (ft_strncmp(&arg[len - 4], ".cub", 5));
}

int	err(char *str, void *ptr)
{
	if (str)
		ft_printf(2, "Error: %s\n", str);
	if (ptr)
		free(ptr);
	return (1);
}

int	free_str_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i])
			free(array[i++]);
	}
	free(array);
	return (1);
}

int	count_commas(char *str)
{
	int	commas;

	commas = 0;
	while (*str != '\0') {
		if (*str == ',')
			commas++;
		str++;
	}
	return (commas);
}

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
	char **rgb;
	
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

int	check_identifier(char **element, t_cub *data)
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
		data->no = copy;
	else if (!ft_strncmp("WE", element[0], 3))
		data->we = copy;
	else if (!ft_strncmp("EA", element[0], 3))
		data->ea = copy;
	else if (!ft_strncmp("SO", element[0], 3))
		data->so = copy;
	else
		return (err("invalid .cub file content", copy));
	return (0);
}

int	parse_element(t_cub *data, char *line)
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

int	get_map_height(t_cub *data, char *line, int fd)
{
	while (line && ft_strchr("1 ", *line))
	{
		data->map.height++;
		free(line);
		line = get_next_line(fd); // malloc/open check
	}
	close(fd);
	if (line)
		return (err("invalid .cub file content", line));
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
		if (ft_strchr("1 ", *line)) {
			data->map.layout[i++] = ft_substr(line, 0, ft_strlen(line) - 1);
			if (!data->map.layout[i - 1])
				return (err("malloc failed", line));
		}
		free(line);
		line = get_next_line(fd); // malloc/open check
	}
	data->map.layout[i] = NULL;
	return (0);
}

int	validate_index(t_cub *data, char **layout, int x, int y)
{
	if (x == 0 || y == 0 || y == data->map.height - 1
		|| x == (int)ft_strlen(layout[y]) - 1)
		return (err("map must be surrounded by walls", NULL));
	if (ft_strchr("NSWE", layout[y][x]))
	{
		if (data->map.orientation)
			return (err("multiple starting positions found in the map", NULL));
		data->map.orientation = layout[y][x];
		return (0);
	}
	if (!ft_strchr("01NSWE", layout[y][x - 1])
		|| !ft_strchr("01NSWE", layout[y][x + 1])
		|| !ft_strchr("01NSWE", layout[y - 1][x])
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
				if (validate_index(data, data->map.layout, x, y))
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

int	parse_map(t_cub *data, char *line, int fd, char *file)
{
	if (data->elements_found != 6)
		return (err("required elements not found in .cub file", line));
	if (get_map_height(data, line, fd))
		return (1);
	if (copy_map(data, fd, file))
		return (1);
	if (validate_map(data))
		return (1);
	return (0);
}

int	parse_file(t_cub *data, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (err("open failed", NULL));
	line = get_next_line(fd); // add malloc/open check for gnl
	while (line && *line != '1' && *line != ' ')
	{
		if (ft_strchr("NSWEFC", *line)) {
			if (parse_element(data, line))
				return (err(NULL, line));
		}
		else if (*line != '\n')
			return (err("invalid .cub file content", line));
		free(line);
		line = get_next_line(fd); // malloc/open check
	}
	if (line && ft_strchr(" 1", *line))
		return (parse_map(data, line, fd, file));
	else
		return (err("required elements not found in .cub file", line));
}

int	free_data(t_cub *data)
{
	if (data->no)
		free(data->no);
	if (data->so)
		free(data->so);
	if (data->we)
		free(data->we);
	if (data->ea)
		free(data->ea);
	if (data->map.layout)
		free_str_array(data->map.layout);
	return (1);
}

int	main(int argc, char **argv)
{
	t_cub	data;

	data = (t_cub){0};
	if (argc != 2 || check_extension(argv[1]))
		return (err("program takes one .cub file as an argument", NULL));
	if (parse_file(&data, argv[1]))
		return (free_data(&data));
	ft_printf(1, "NO: %s\n", data.no);
	ft_printf(1, "SO: %s\n", data.so);
	ft_printf(1, "WE: %s\n", data.we);
	ft_printf(1, "EA: %s\n", data.ea);
	ft_printf(1, "floor: %d,%d,%d\n", data.floor[0], data.floor[1], data.floor[2]);
	ft_printf(1, "ceiling: %d,%d,%d\n", data.ceiling[0], data.ceiling[1], data.ceiling[2]);
	ft_printf(1, "map height: %d\n", data.map.height);
	for (int i = 0; i < data.map.height; i++)
		ft_printf(1, "%s\n", data.map.layout[i]);
	free_data(&data);
	return (0);
}
