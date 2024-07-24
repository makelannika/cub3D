/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:51:00 by amakela           #+#    #+#             */
/*   Updated: 2023/11/16 15:53:45 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*exceptions(int n);
static char	*allocatencpy(char *temp, int i, int neg);

char	*ft_itoa(int n)
{
	int		i;
	int		neg;
	char	temp[11];

	i = 0;
	neg = 0;
	if (n == 0 || n == -2147483648)
		return (exceptions(n));
	if (n < 0)
	{
		neg = 1;
		n = -n;
	}
	while (n >= 1)
	{
		temp[i++] = n % 10 + '0';
		n = n - n % 10;
		n = n / 10;
	}
	return (allocatencpy(temp, i, neg));
}

static char	*exceptions(int n)
{
	char	*str;

	if (n == 0)
	{
		str = malloc (2);
		if (!str)
			return (NULL);
		ft_strlcpy(str, "0", 2);
		return (str);
	}
	if (n == -2147483648)
	{
		str = malloc (12);
		if (!str)
			return (NULL);
		ft_strlcpy(str, "-2147483648", 12);
		return (str);
	}
	return (0);
}

static char	*allocatencpy(char *temp, int i, int neg)
{
	char	*str;
	int		j;

	j = 0;
	str = malloc (i + neg + 1);
	if (!str)
		return (NULL);
	if (neg == 1)
		str[j++] = '-';
	while (i > 0)
		str[j++] = temp[i-- -1];
	str[j] = '\0';
	return (str);
}
