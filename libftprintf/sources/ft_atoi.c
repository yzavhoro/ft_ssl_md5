/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzavhoro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 14:07:52 by yzavhoro          #+#    #+#             */
/*   Updated: 2018/03/27 18:13:56 by yzavhoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int						i;
	int						sgn;
	unsigned long long int	res;

	i = 0;
	sgn = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == ' '))
		i++;
	if (str[i] == '-')
		sgn = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if ((res > 2147483647 && sgn == 1) || (res > 2147483648 && sgn == -1))
		{
			ft_putstr("ERROR: given value doesn't fit to an int\n");
			exit(0);
		}
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return ((int)res * sgn);
}
