/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:53:43 by amakela           #+#    #+#             */
/*   Updated: 2023/11/10 21:56:17 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	if (dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	j = ft_strlen(dst);
	while ((src[i]) && (j < (dstsize - 1)))
	{
		dst[j] = src[i];
		i ++;
		j ++;
	}
	if (dstsize > (j - i))
		dst[j] = '\0';
	if (dstsize < (j - i))
		return (dstsize + ft_strlen(src));
	return (ft_strlen(src) + (j - i));
}
