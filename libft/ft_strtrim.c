/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:34:33 by amakela           #+#    #+#             */
/*   Updated: 2023/11/11 16:47:36 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	s1len;
	char			*str;

	i = 0;
	if (s1 == 0)
		return (0);
	if (!set)
		return ((char *)s1);
	s1len = ft_strlen(s1);
	if (s1len > 0)
	{
		while (ft_strchr(set, s1[i]))
			i ++;
		if (i < s1len)
			while (ft_strchr(set, s1[s1len - 1]))
				s1len --;
	}
	if (i > s1len)
		return (ft_calloc(1, 1));
	str = malloc (s1len - i + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[i], s1len - i + 1);
	return (str);
}
