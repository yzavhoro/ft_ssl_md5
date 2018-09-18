/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzavhoro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 16:52:08 by yzavhoro          #+#    #+#             */
/*   Updated: 2018/09/09 16:52:11 by yzavhoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_commands	g_cmds[] = {
	{"md5", hash_md5},
	{"sha256", hash_sha256}
};

int		main(int ac, char **av)
{
	t_ssl	ssl;

	if (ac == 1)
		display_programme_usage();
	else
	{
		ft_bzero((void*)&ssl, sizeof(t_ssl));
		validate_command(av, &ssl);
	}
	return (0);
}
