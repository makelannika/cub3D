/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:34:52 by linhnguy          #+#    #+#             */
/*   Updated: 2024/07/26 19:41:26 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_map_char(t_cub *data)
{
	int	i;
	int j;
	int flag;

	i = 0;
	flag = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == ' ' || data->map[i][j] == '1' || data->map[i][j] == '0')
				;
			else if (!flag && (data->map[i][j] == 'N'|| data->map[i][j] == 'W'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'S'))
				flag = 1;
			else 
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int increase_array_capacity(t_cub *data, int *capacity)
{
	char 	**new_array;
	int		new_capacity;
	int		i;

	i = 0;
	new_capacity = *capacity * 2;
	new_array = malloc(sizeof(char *) * new_capacity);
	if (!new_array)
		return (1);
	while (data->map[i])
	{
		new_array[i] = data->map[i];
		i++;
	}
	free (data->map);
	data->map = new_array;
	*capacity = new_capacity;
	return (0);
}

int	init_map(int fd, t_cub *data, char *line)
{
	int		capacity;
	int		i;

	i = 0;
	capacity = 2;
	data->map = malloc(sizeof(char *) * capacity);
	while (line)
	{
		data->map[i] = strdup_no_newline(line);
		if (!data->map[i])
			return (1); //needs free funciton that checks array index and free in cleanup;
		i++;
		data->map[i] = NULL;
		if (i == capacity - 1)
		{
			if (increase_array_capacity(data, &capacity))
				return (1); //needs free funciton that checks array index and free in cleanup;
		}
		free (line);
		line = get_next_line(fd); // check line
	}
	return (0);
}
