/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzavhoro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 16:53:03 by yzavhoro          #+#    #+#             */
/*   Updated: 2018/09/09 16:53:06 by yzavhoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include "ft_printf.h"
# include "get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <stdint.h>

# define BS 1024
# define CMDS 2

# define ILLEGAL_OPTION 0
# define ARG_REQUIRED 1
# define IS_DIRECTORY 2

# define LROTATE(x, c) (((x) << (c)) | ((x) >> (32 - (c))))
# define RROTATE(x, c) (((x) >> (c)) | ((x) << (32 - (c))))

# define SHA256_BLOCK_SIZE 32
# define CH(x,y,z) (((x) & (y)) ^ (~(x) & (z)))
# define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define EP0(x) (RROTATE(x,2) ^ RROTATE(x,13) ^ RROTATE(x,22))
# define EP1(x) (RROTATE(x,6) ^ RROTATE(x,11) ^ RROTATE(x,25))
# define SIG0(x) (RROTATE(x,7) ^ RROTATE(x,18) ^ ((x) >> 3))
# define SIG1(x) (RROTATE(x,17) ^ RROTATE(x,19) ^ ((x) >> 10))

typedef struct	s_ssl
{
	int			cmd;
	char		flag_r;
	char		flag_q;
	char		flag_p;
}				t_ssl;

typedef struct	s_commands
{
	char		*name;
	void		(*hash_fun)(char *);
}				t_commands;

typedef struct	s_md5
{
	uint8_t		*msg;
	int			new_len;
	int			offset;
	uint32_t	*w;
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	f;
	uint32_t	g;
}				t_md5;

typedef struct	s_sha256
{
	uint8_t		data[64];
	uint32_t	datalen;
	uint64_t	bitlen;
	uint32_t	state[8];
	uint32_t	a;
	uint32_t	b;
	uint32_t	c;
	uint32_t	d;
	uint32_t	e;
	uint32_t	f;
	uint32_t	g;
	uint32_t	h;
	uint32_t	t1;
	uint32_t	t2;
	uint32_t	m[64];
}				t_sha256;

extern	t_commands g_cmds[];

/*
**	validate_command.c
*/

void			validate_command(char **av, t_ssl *ssl);
void			validate_flags(char **av, t_ssl *ssl);
void			hash_all(char **av, int i, t_ssl *ssl, int flag);

/*
**	hash.c
*/

char			*get_text(int fd);
void			hash_string(char *str, t_ssl *ssl);
void			hash_stdin(int flag, t_ssl *ssl);
void			hash_file(char *filename, int fd, t_ssl *ssl);

/*
**	md5.c
*/

void			hash_md5(char *msg);
void			hash_cycle(int i, t_md5 *md, uint32_t temp);
void			main_cycle(t_md5 *md);
void			md5(uint8_t *initial_msg, size_t initial_len);

/*
**	sha256.c
*/

void			hash_sha256(char *msg);
void			sha256_final(t_sha256 *ctx, uint8_t *hash);
void			sha256_transform(t_sha256 *ctx, uint8_t *data);
void			sha256_transform2(t_sha256 *ctx);
void			sha256_fin_fill(t_sha256 *ctx, uint8_t *hash);

/*
**	sha256_adds.c
*/

void			sha256_init(t_sha256 *ctx);
void			sha256_fill_vars(t_sha256 *ctx, int id);
void			sha256_update(t_sha256 *ctx, uint8_t *data, size_t len);

/*
**	adds.c
*/

void			display_programme_usage(void);
void			display_invalid_command(char *command);
void			display_error(char *arg, int cmd);
int				is_flag(char *arg);
void			display_command_usage(char *arg, int cmd, int code);

#endif
