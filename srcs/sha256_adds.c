/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_adds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzavhoro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 18:19:30 by yzavhoro          #+#    #+#             */
/*   Updated: 2018/09/12 18:19:31 by yzavhoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			sha256_init(t_sha256 *ctx)
{
	ctx->datalen = 0;
	ctx->bitlen = 0;
	ctx->state[0] = 0x6a09e667;
	ctx->state[1] = 0xbb67ae85;
	ctx->state[2] = 0x3c6ef372;
	ctx->state[3] = 0xa54ff53a;
	ctx->state[4] = 0x510e527f;
	ctx->state[5] = 0x9b05688c;
	ctx->state[6] = 0x1f83d9ab;
	ctx->state[7] = 0x5be0cd19;
}

void			sha256_fill_vars(t_sha256 *ctx, int id)
{
	if (id == 1)
	{
		ctx->a = ctx->state[0];
		ctx->b = ctx->state[1];
		ctx->c = ctx->state[2];
		ctx->d = ctx->state[3];
		ctx->e = ctx->state[4];
		ctx->f = ctx->state[5];
		ctx->g = ctx->state[6];
		ctx->h = ctx->state[7];
	}
	else if (id == 2)
	{
		ctx->state[0] += ctx->a;
		ctx->state[1] += ctx->b;
		ctx->state[2] += ctx->c;
		ctx->state[3] += ctx->d;
		ctx->state[4] += ctx->e;
		ctx->state[5] += ctx->f;
		ctx->state[6] += ctx->g;
		ctx->state[7] += ctx->h;
	}
}

void			sha256_update(t_sha256 *ctx, uint8_t *data, size_t len)
{
	uint32_t i;

	i = -1;
	while (++i < len)
	{
		ctx->data[ctx->datalen] = data[i];
		ctx->datalen++;
		if (ctx->datalen == 64)
		{
			sha256_transform(ctx, ctx->data);
			ctx->bitlen += 512;
			ctx->datalen = 0;
		}
	}
}
