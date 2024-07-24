/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 12:25:22 by amakela           #+#    #+#             */
/*   Updated: 2024/07/24 18:13:52 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t		i;
	char		*str;

	if (n == 0)
		return ;
	i = 0;
	str = s;
	while (i < n)
	{
		str[i] = 0;
		i ++;
	}
}
