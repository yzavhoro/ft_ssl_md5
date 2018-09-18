/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzavhoro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/09 16:52:26 by yzavhoro          #+#    #+#             */
/*   Updated: 2018/09/09 16:52:33 by yzavhoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static			uint32_t g_h0;
static			uint32_t g_h1;
static			uint32_t g_h2;
static			uint32_t g_h3;

static const	uint32_t g_r[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static const	uint32_t g_k[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

void			hash_cycle(int i, t_md5 *md, uint32_t temp)
{
	if (i < 16)
	{
		md->f = (md->b & md->c) | ((~md->b) & md->d);
		md->g = i;
	}
	else if (i < 32)
	{
		md->f = (md->d & md->b) | ((~md->d) & md->c);
		md->g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		md->f = md->b ^ md->c ^ md->d;
		md->g = (3 * i + 5) % 16;
	}
	else
	{
		md->f = md->c ^ (md->b | (~md->d));
		md->g = (7 * i) % 16;
	}
	temp = md->d;
	md->d = md->c;
	md->c = md->b;
	md->b = md->b + LROTATE((md->a + md->f + g_k[i] + md->w[md->g]), g_r[i]);
	md->a = temp;
}

void			main_cycle(t_md5 *md)
{
	uint32_t i;

	while (md->offset < md->new_len)
	{
		md->w = (uint32_t*)(md->msg + md->offset);
		md->a = g_h0;
		md->b = g_h1;
		md->c = g_h2;
		md->d = g_h3;
		i = -1;
		while (++i < 64)
			hash_cycle(i, md, 0);
		g_h0 += md->a;
		g_h1 += md->b;
		g_h2 += md->c;
		g_h3 += md->d;
		md->offset += 512 / 8;
	}
}

void			md5(uint8_t *initial_msg, size_t initial_len)
{
	t_md5		md;
	uint32_t	bits_len;

	g_h0 = 0x67452301;
	g_h1 = 0xefcdab89;
	g_h2 = 0x98badcfe;
	g_h3 = 0x10325476;
	md.new_len = initial_len * 8 + 1;
	while (md.new_len % 512 != 448)
		md.new_len++;
	md.new_len /= 8;
	md.msg = (uint8_t*)ft_memalloc(md.new_len + 64);
	ft_memcpy(md.msg, initial_msg, initial_len);
	md.msg[initial_len] = 128;
	bits_len = 8 * initial_len;
	ft_memcpy(md.msg + md.new_len, &bits_len, 4);
	md.offset = 0;
	main_cycle(&md);
	free(md.msg);
}

void			hash_md5(char *msg)
{
	size_t	len;
	uint8_t	*p;

	len = strlen(msg);
	md5((uint8_t*)msg, len);
	p = (uint8_t *)&g_h0;
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&g_h1;
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&g_h2;
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
	p = (uint8_t *)&g_h3;
	ft_printf("%2.2x%2.2x%2.2x%2.2x", p[0], p[1], p[2], p[3]);
}
