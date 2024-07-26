/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:37:42 by linhnguy          #+#    #+#             */
/*   Updated: 2024/07/26 19:51:21 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	copy_path(char *line, char *id)
{
	id = ft_substr(line, 0, ft_strlen(line) - 1);
	if (!id)
		return (err("malloc failed in substr"));
	return (0);
}

int	copy_color(char *line, int *id)
{
	char	**rgb;

	while (*line == ' ')
		line++;
	//check the rgb is a good string
	rgb = ft_split(line, ',');
	if (!rgb)
		return (err("malloc failed in split"));
	id[0] = ft_atoi(rgb[0]);
	id[1] = ft_atoi(rgb[1]);
	id[2] = ft_atoi(rgb[2]);
	return (0);
}

int	check_identifier(char *line, t_cub *data)
{
	if (!ft_strncmp("NO ", line, 3))
		return (copy_path(line, data->no));
	if (!ft_strncmp("WE ", line, 3))
		return (copy_path(line, data->we));
	if (!ft_strncmp("EA ", line, 3))
		return (copy_path(line, data->ea));
	if (!ft_strncmp("SO ", line, 3))
		return (copy_path(line, data->so));
	if (!ft_strncmp("F ", line, 2))
		return (copy_color(&line[1], data->floor));
	if (!ft_strncmp("C ", line, 2))
		return (copy_color(&line[1], data->ceiling));
	return (0);
}
