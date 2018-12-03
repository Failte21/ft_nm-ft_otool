/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:44:03 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/03 08:09:45 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

//This files contains functions to print the symbols previously store in a 
//binary tree of t_sym

//Todo: remove printf

// static void	print_header_o(char *fname, char *oname)
// {
// 	ft_putchar('\n');
// 	ft_putstr(fname);
// 	ft_putchar('(');
// 	ft_putstr(oname);
// 	ft_putstr("):\n");
// }

static void	print_header_fat(char *fname, char *archname)
{
	ft_putchar('\n');
	ft_putstr(fname);
	ft_putstr(" (");
	ft_putstr("for architecture ");
	ft_putstr(archname);
	ft_putstr("):\n");
}

static void	print_header(char *fname)
{
	ft_putchar('\n');
	ft_putstr(fname);
	ft_putstr(":\n");
}

static void print_header_lib(char *fname, char *oname)
{
	ft_putchar('\n');
	ft_putstr(fname);
	ft_putchar('(');
	ft_putstr(oname);
	ft_putstr("):\n");
}

static int	print_infos(t_print_infos *curr, char *name, enum ftype type, bool multiple)
{
	int	err;

	err = 0;
	if (curr)
	{
		if (type == MH && multiple)
			print_header(name);
		if (type == LIB)
			print_header_lib(name, curr->name);
		if (type == FAT && curr->cputype != CPU_TYPE_X86_64)
			print_header_fat(name, get_archname(curr->cputype, curr->cpusubtype));
		if (curr->failed)
		{
			ft_putstr_fd("An error occured\n", 2);
			err++;
		}
		//TODO: print main stuff
		print_infos(curr->next, name, type, multiple);
	}
	return (err);
}

int			print_file(t_file *f, char *name, bool multiple)
{
	return (print_infos(f->head, name, f->type, multiple));
}