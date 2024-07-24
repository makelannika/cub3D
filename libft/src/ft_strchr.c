/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:24:26 by amakela           #+#    #+#             */
/*   Updated: 2024/07/24 18:14:18 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	length;
	size_t	i;
	char	ch;

	i = 0;
	ch = (char)c;
	length = ft_strlen(s);
	while (i <= length)
		if (s[i] != ch)
			i++;
	else
		return ((char *)&s[i]);
	return (0);
}
