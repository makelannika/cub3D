/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 12:36:24 by linhnguy          #+#    #+#             */
/*   Updated: 2024/07/26 19:33:42 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	err(char *str)
{
	ft_printf(2, "%s\n", str);
	return (1);
}

char	*strdup_no_newline(const char *s1)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = malloc (ft_strlen(s1) + 1);
	if (ptr == 0)
		return (NULL);
	while (s1[i])
	{
		if (s1[i] == '\n')
			i++;
		ptr[i] = s1[i];
		i ++;
	}
	ptr[i] = '\0';
	return (ptr);
}

int	check_extension(char *arg)
{
	int     len;

	len = ft_strlen(arg);
	return (ft_strncmp(&arg[len - 4], ".cub", 5));
}
