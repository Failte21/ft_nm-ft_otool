/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_32.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 09:36:01 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/05 11:17:39 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

void print_dump_32_block(t_hex_dump *hp, bool swap)
{
	uint32_t 	i;
	uint32_t	off;
	uint32_t	e;

	i = 0;
	off = sizeof(uint32_t);
	while (i < hp->sec32->size)
	{
		if (i % 16 == 0)
		{
			if (i)
				ft_putchar('\n');
			ft_put_hex_precision(hp->sec32->addr + i, 8);
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

void print_dump_32_space(t_hex_dump *hp)
{
	uint32_t	i;

	i = 0;
	while (i < hp->sec32->size)
	{
		if (i % 16 == 0)
		{
			if (i)
				ft_putchar('\n');
			ft_put_hex_precision(hp->sec32->addr + i, 8);
			ft_putchar('\t');
		}
		ft_put_hex_precision(hp->datas[i], 2);
		ft_putchar(' ');
		i++;
	}
	if (i)
		ft_putchar('\n');
}