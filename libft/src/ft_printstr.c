/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:29:43 by amakela           #+#    #+#             */
/*   Updated: 2024/07/24 18:14:18 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	ft_printstr(int fd, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_printstr(fd, "(null)"));
	while (str[i])
		if (ft_printchar(fd, str[i++]) == -1)
			return (-1);
	return (i);
}
