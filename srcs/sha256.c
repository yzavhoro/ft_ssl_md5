/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzavhoro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/11 15:01:39 by yzavhoro          #+#    #+#             */
/*   Updated: 2018/09/11 15:01:40 by yzavhoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static const	uint32_t g_k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

void			sha256_transform2(t_sha256 *ctx)
{
	uint32_t i;

	i = -1;
	while (++i < 64)
	{
		ctx->t1 =
		ctx->h + EP1(ctx->e) + CH(ctx->e, ctx->f, ctx->g) + g_k[i] + ctx->m[i];
		ctx->t2 = EP0(ctx->a) + MAJ(ctx->a, ctx->b, ctx->c);
		ctx->h = ctx->g;
		ctx->g = ctx->f;
		ctx->f = ctx->e;
		ctx->e = ctx->d + ctx->t1;
		ctx->d = ctx->c;
		ctx->c = ctx->b;
		ctx->b = ctx->a;
		ctx->a = ctx->t1 + ctx->t2;
	}
	sha256_fill_vars(ctx, 2);
}

void			sha256_transform(t_sha256 *ctx, uint8_t *data)
{
	uint32_t i;
	uint32_t j;

	i = -1;
	j = 0;
	while (++i < 16)
	{
		ctx->m[i] = (data[j] << 24) | (data[j + 1] << 16)
		| (data[j + 2] << 8) | (data[j + 3]);
		j += 4;
	}
	while (i < 64)
	{
		ctx->m[i] = SIG1(ctx->m[i - 2]) + ctx->m[i - 7]
		+ SIG0(ctx->m[i - 15]) + ctx->m[i - 16];
		i++;
	}
	sha256_fill_vars(ctx, 1);
	sha256_transform2(ctx);
}

void			sha256_fin_fill(t_sha256 *ctx, uint8_t *hash)
{
	uint32_t i;
	uint32_t j;

	i = -1;
	while (++i < 8)
		ctx->data[63 - i] = ctx->bitlen >> (i * 8);
	sha256_transform(ctx, ctx->data);
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 8)
			hash[i + (j << 2)] = (ctx->state[j] >> (24 - i * 8)) & 0x000000ff;
	}
}

void			sha256_final(t_sha256 *ctx, uint8_t *hash)
{
	uint32_t i;

	i = ctx->datalen;
	if (ctx->datalen < 56)
	{
		ctx->data[i++] = 0x80;
		while (i < 56)
			ctx->data[i++] = 0x00;
	}
	else
	{
		ctx->data[i++] = 0x80;
		while (i < 64)
			ctx->data[i++] = 0x00;
		sha256_transform(ctx, ctx->data);
		ft_memset(ctx->data, 0, 56);
	}
	ctx->bitlen += ctx->datalen * 8;
	sha256_fin_fill(ctx, hash);
}

void			hash_sha256(char *msg)
{
	t_sha256	ctx;
	uint8_t		buf[SHA256_BLOCK_SIZE];
	int			i;

	sha256_init(&ctx);
	sha256_update(&ctx, (uint8_t*)msg, strlen(msg));
	sha256_final(&ctx, buf);
	i = -1;
	while (++i < 8)
		ft_printf("%.8x", ctx.state[i]);
}
