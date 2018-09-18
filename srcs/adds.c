/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzavhoro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 16:49:47 by yzavhoro          #+#    #+#             */
/*   Updated: 2018/09/09 16:49:52 by yzavhoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	display_programme_usage(void)
{
	ft_putendl("usage: ft_ssl command [command opts] [command args]");
}

void	display_invalid_command(char *command)
{
	ft_printf("ft_ssl: Error: %s is an invalid command.\n", command);
	ft_putendl("\nStandard commands:\n");
	ft_putendl("Message Digest commands:\nmd5\nsha256\n");
	ft_putendl("Cipher commands:");
	exit(0);
}

void	display_error(char *arg, int cmd)
{
	ft_printf("ft_ssl: %s: %s: %s\n",
		g_cmds[cmd].name, arg, strerror(errno));
}

int		is_flag(char *arg)
{
	return (arg[0] && arg[1] && arg[0] == '-');
}

void	display_command_usage(char *arg, int cmd, int code)
{
	if (code == ILLEGAL_OPTION)
		ft_printf("ft_ssl: %s: illegal option -- %s\n",\
			g_cmds[cmd].name, arg);
	else if (code == ARG_REQUIRED)
		ft_printf("ft_ssl: %s: option requires an argument -- s\n",\
			g_cmds[cmd].name);
	else if (code == IS_DIRECTORY)
	{
		ft_printf("ft_ssl: %s: %s: Is a directory\n", g_cmds[cmd].name, arg);
		return ;
	}
	ft_printf("usage: ft_ssl %s [-pqr] [-s string] [files ...]\n",
		g_cmds[cmd].name);
	exit(0);
}
