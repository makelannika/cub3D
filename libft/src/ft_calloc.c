/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:07:12 by amakela           #+#    #+#             */
/*   Updated: 2024/07/24 18:24:19 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdint.h>

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;

	if (size != 0 && count > (SIZE_MAX / size))
		return (NULL);
	ptr = malloc (count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, (count * size));
	return (ptr);
}
