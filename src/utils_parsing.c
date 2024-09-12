/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:33:08 by amakela           #+#    #+#             */
/*   Updated: 2024/09/12 16:46:48 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	validate_line(char *str)
{
	while (*str)
	{
		if (!ft_strchr(" 10NSWE\n", *str))
			return (1);
		str++;
	}
	return (0);
}

void get_map_width(t_cub3d *data)
{
	int i;

	i = 0;
	while (data->map.map[i])
	{
		if ((int)ft_strlen(data->map.map[i]) > data->map.map_width)
			data->map.map_width = ft_strlen(data->map.map[i]);
		i++;
	}
}

int	get_map_height(t_cub3d *data, char *line, int fd)
{
	while (line && ft_strchr("1 ", *line))
	{
		if (validate_line(line))
		{
			close(fd);
			return (err("invalid map", line));
		}
		data->map.map_height++;
		free(line);
		line = get_next_line(fd); // malloc/open check
	}
	close(fd);
	if (line)
		return (err("invalid .cub file content", line));
	return (0);
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

int	check_extension(char *arg)
{
	int     len;

	len = ft_strlen(arg);
	return (ft_strncmp(&arg[len - 4], ".cub", 5));
}
