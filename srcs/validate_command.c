/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzavhoro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 16:52:46 by yzavhoro          #+#    #+#             */
/*   Updated: 2018/09/09 16:52:49 by yzavhoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	hash_all(char **av, int i, t_ssl *ssl, int flag)
{
	int fd;

	if (av[i] == NULL && flag)
		hash_stdin(0, ssl);
	else
	{
		while (av[i])
		{
			fd = open(av[i], O_RDONLY);
			if (fd == -1)
				display_error(av[i], ssl->cmd);
			else
				hash_file(av[i], fd, ssl);
			i++;
		}
	}
}

void	validate_flags(char **av, t_ssl *ssl)
{
	int	i;
	int ifstdin;

	i = 2;
	ifstdin = 1;
	while (av[i] && is_flag(av[i]))
	{
		if (!ft_strcmp(av[i], "-q"))
			ssl->flag_q = 1;
		else if (!ft_strcmp(av[i], "-r"))
			ssl->flag_r = 1;
		else if (!ft_strcmp(av[i], "-p") && !(ifstdin = 0))
			hash_stdin(1, ssl);
		else if (!ft_strcmp(av[i], "-s") && !(ifstdin = 0))
		{
			if (!av[i + 1])
				display_command_usage(NULL, ssl->cmd, ARG_REQUIRED);
			else
				hash_string(av[++i], ssl);
		}
		else
			display_command_usage(av[i] + 1, ssl->cmd, ILLEGAL_OPTION);
		i++;
	}
	hash_all(av, i, ssl, ifstdin);
}

void	validate_command(char **av, t_ssl *ssl)
{
	int i;

	i = 0;
	while (i < CMDS && ft_strcmp(av[1], g_cmds[i].name))
		i++;
	if (i == CMDS)
		display_invalid_command(av[1]);
	ssl->cmd = i;
	if (av[2])
		validate_flags(av, ssl);
	else
		hash_stdin(0, ssl);
}
