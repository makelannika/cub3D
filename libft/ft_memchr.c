/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:22:24 by amakela           #+#    #+#             */
/*   Updated: 2023/11/17 17:38:01 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	unsigned const char		*str;
	unsigned char			ch;

	i = 0;
	str = s;
	ch = c;
	while (i < n)
	{
		if (str[i] == ch)
			return ((void *)&str[i]);
		i ++;
	}
	return (0);
}
