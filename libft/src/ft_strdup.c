/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:34:07 by amakela           #+#    #+#             */
/*   Updated: 2024/07/24 18:14:18 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = malloc (ft_strlen(s1) + 1);
	if (ptr == 0)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i ++;
	}
	ptr[i] = '\0';
	return (ptr);
}
