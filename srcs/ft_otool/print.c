/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:44:03 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/03 11:00:02 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

static void	print_header_fat(char *fname, char *archname)
{
	ft_putstr(fname);
	ft_putstr(" (");
	ft_putstr("for architecture ");
	ft_putstr(archname);
	ft_putstr("):\n");
}

static void	print_header(char *fname)
{
	ft_putstr(fname);
	ft_putstr(":\n");
}

static void print_header_lib(char *fname, char *oname)
{
	ft_putstr(fname);
	ft_putchar('(');
	ft_putstr(oname);
	ft_putstr("):\n");
}

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

static void print_dump_32(t_hex_dump *hp)
{
	uint32_t i;

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

static int	print_infos(t_print_infos *curr, char *name, enum ftype type)
{
	int	err;

	err = 0;
	if (curr)
	{
		if (type == LIB)
			print_header_lib(name, curr->name);
		if (type == FAT && curr->cputype != CPU_TYPE_X86_64)
			print_header_fat(name, get_archname(curr->cputype, curr->cpusubtype));
		else
			print_header(name);
		if (curr->failed)
		{
			ft_putstr_fd("An error occured\n", 2);
			err++;
		}
		//TODO: print main stuff
		ft_putstr("Contents of (__TEXT,__text) section\n");
		if (curr->is_64)
			print_dump_64(curr->hex_dump);
		else
			print_dump_32(curr->hex_dump);
		print_infos(curr->next, name, type);
	}
	return (err);
}

int			print_file(t_file *f, char *name)
{
	return (print_infos(f->head, name, f->type));
}