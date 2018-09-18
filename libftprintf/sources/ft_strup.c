/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzavhoro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/10 19:21:01 by yzavhoro          #+#    #+#             */
/*   Updated: 2018/09/10 19:21:02 by yzavhoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strup(char *str)
{
	int		i;
	char	*upper_str;

	i = 0;
	if (!str)
		return (NULL);
	upper_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i])
	{
		upper_str[i] = ft_toupper(str[i]);
		i++;
	}
	upper_str[i] = '\0';
	return (upper_str);
}
