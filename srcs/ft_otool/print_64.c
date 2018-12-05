/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 09:37:03 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/05 11:17:20 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

void print_dump_64_space(t_hex_dump *hp)
{
	uint64_t	i;

	i = 0;
	while (i < hp->sec64->size)
	{
		if (i % 16 == 0)
		{
			if (i)
				ft_putchar('\n');
			ft_put_hex_precision(hp->sec64->addr + i, 16);
			ft_putchar('\t');
		}
		ft_put_hex_precision(hp->datas[i], 2);
		ft_putchar(' ');
		i++;
	}
	if (i)
		ft_putchar('\n');
}

void print_dump_64_block(t_hex_dump *hp, bool swap)
{
	uint64_t	i;
	uint32_t	off;
	uint32_t	e;

	i = 0;
	off = sizeof(uint32_t);
	while (i < hp->sec64->size)
	{
		if (i % 16 == 0)
		{
			if (i)
				ft_putchar('\n');
			ft_put_hex_precision(hp->sec64->addr + i, 16);
			ft_putchar('\t');
		}
		e = *((uint32_t *)(hp->datas + i));
		e = swap ? swap_int32(e) : e;
		ft_put_hex_precision(e, 8);
		ft_putchar(' ');
		i += off;
	}
	if (i)
		ft_putchar('\n');
}