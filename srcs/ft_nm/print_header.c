/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 09:19:16 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/07 13:28:50 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

static void	print_header_fat(char *fname, char *archname)
{
	ft_putchar('\n');
	ft_putstr(fname);
	ft_putstr(" (");
	ft_putstr("for architecture ");
	ft_putstr(archname);
	ft_putstr("):\n");
}

static void	print_header_simple(char *fname)
{
	ft_putchar('\n');
	ft_putstr(fname);
	ft_putstr(":\n");
}

static void	print_header_lib(char *fname, char *oname)
{
	ft_putchar('\n');
	ft_putstr(fname);
	ft_putchar('(');
	ft_putstr(oname);
	ft_putstr("):\n");
}

void		print_header(enum e_ftype type, bool multiple,\
	char *name, t_print_infos *curr)
{
	if (type == MH && multiple)
		print_header_simple(name);
	if (type == LIB)
		print_header_lib(name, curr->name);
	if (type == FAT && curr->cputype != CPU_TYPE_X86_64)
		print_header_fat(name, get_archname(curr->cputype, curr->cpusubtype));
}
