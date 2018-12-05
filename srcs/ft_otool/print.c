/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:44:03 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/05 09:12:34 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

static void print_dump_64(t_hex_dump *hp)
{
	uint64_t i;

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
	ft_putchar('\n');
}

static void print_dump_32_space(t_hex_dump *hp)
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
	ft_putchar('\n');
}

static void print_dump_32_block(t_hex_dump *hp, bool swap)
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
	ft_putchar('\n');
}

static int	print_infos(t_print_infos *curr, char *name, enum ftype type)
{
	int	err;

	err = 0;
	if (curr)
	{
		print_header(type, name, curr);
		if (curr->failed)
		{
			ft_putstr_fd("An error occured\n", 2);
			err++;
		}
		ft_putstr("Contents of (__TEXT,__text) section\n");
		if (curr->cputype == CPU_TYPE_I386 || curr->cputype == CPU_TYPE_X86_64)
		{
			if (curr->is_64)
				print_dump_64(curr->hex_dump);
			else
				print_dump_32_space(curr->hex_dump);
		}
		else
		{
			if (curr->is_64)
				print_dump_64(curr->hex_dump);
			else
				print_dump_32_block(curr->hex_dump, curr->swap);
		}
		print_infos(curr->next, name, type);
	}
	return (err);
}

int			print_file(t_file *f, char *name)
{
	return (print_infos(f->head, name, f->type));
}