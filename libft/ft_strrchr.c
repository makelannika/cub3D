/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:23:22 by amakela           #+#    #+#             */
/*   Updated: 2023/11/10 13:30:22 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ch;

	ch = (char)c;
	i = ft_strlen(s);
	while (i >= 0)
		if (s[i] != ch)
			i --;
	else if (s[i] == ch)
		return ((char *) &s[i]);
	return (0);
}
