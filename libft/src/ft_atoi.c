/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:39:48 by amakela           #+#    #+#             */
/*   Updated: 2023/11/16 15:51:09 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	overflow(int neg);

int	ft_atoi(const char *str)
{
	int		i;
	long	nbr;
	int		neg;
	long	prev;

	i = 0;
	nbr = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i ++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		if (str[i] == '-')
			neg = -1;
		i ++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		prev = nbr;
		nbr = 10 * nbr + str[i++] - '0';
		if (prev > nbr)
			return (overflow(neg));
	}
	return ((int)nbr * neg);
}

static int	overflow(int neg)
{
	if (neg == -1)
		return (0);
	return (-1);
}
