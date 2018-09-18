/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzavhoro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 16:51:49 by yzavhoro          #+#    #+#             */
/*   Updated: 2018/09/09 16:51:50 by yzavhoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

char	*get_text(int fd)
{
	char	*str;
	char	buff[BS + 1];
	int		ret;

	str = ft_strnew(0);
	ret = 0;
	while ((ret = read(fd, buff, BS)))
	{
		buff[ret] = '\0';
		str = ft_strjoin(str, buff);
	}
	return (str);
}

void	hash_string(char *str, t_ssl *ssl)
{
	char *command;

	command = ft_strup(g_cmds[ssl->cmd].name);
	if (!ssl->flag_q && !ssl->flag_r)
		ft_printf("%s (\"%s\") = ", command, str);
	g_cmds[ssl->cmd].hash_fun(str);
	if (ssl->flag_r && !ssl->flag_q)
		ft_printf(" \"%s\"", str);
	write(1, "\n", 1);
	free(command);
}

void	hash_stdin(int flag, t_ssl *ssl)
{
	char *str;

	if (ssl->flag_p)
		str = ft_strnew(0);
	else
	{
		str = get_text(0);
		ssl->flag_p = 1;
	}
	if (flag)
		ft_putstr(str);
	g_cmds[ssl->cmd].hash_fun(str);
	write(1, "\n", 1);
	free(str);
}

void	hash_file(char *filename, int fd, t_ssl *ssl)
{
	char		*str;
	struct stat st;
	char		*command;

	lstat(filename, &st);
	if ((st.st_mode & S_IFMT) == S_IFDIR)
	{
		display_command_usage(filename, ssl->cmd, IS_DIRECTORY);
		return ;
	}
	str = get_text(fd);
	command = ft_strup(g_cmds[ssl->cmd].name);
	if (!ssl->flag_q && !ssl->flag_r)
		ft_printf("%s (%s) = ", command, filename);
	g_cmds[ssl->cmd].hash_fun(str);
	if (ssl->flag_r && !ssl->flag_q)
		ft_printf(" %s", filename);
	write(1, "\n", 1);
	free(str);
	free(command);
}
