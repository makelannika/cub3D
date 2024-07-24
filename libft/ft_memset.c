/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:22:43 by amakela           #+#    #+#             */
/*   Updated: 2023/10/31 12:22:47 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char			*ptr;
	size_t			i;
	unsigned char	ch;

	i = 0;
	ptr = b;
	ch = c;
	while (i < len)
	{
		ptr[i] = ch;
		i ++;
	}
	return (b);
}
