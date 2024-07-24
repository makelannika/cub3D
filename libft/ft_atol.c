/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@hive.student.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:53:17 by linhnguy          #+#    #+#             */
/*   Updated: 2024/01/08 15:14:41 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char s)
{
	if ((s >= 9 && s <= 13) || s == 32)
		return (1);
	return (0);
}

long	ft_atol(const char *str)
{
	long	dest;
	long	i;
	long	neg;

	dest = 0;
	i = 0;
	neg = 1;
	while (ft_isspace(str[i]))
		i++;
	if ((str[i] == 45 || str[i] == 43))
	{
		if (str[i] == 45)
			neg = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
		dest = dest * 10 + str[i++] - '0';
	return (dest * neg);
}
