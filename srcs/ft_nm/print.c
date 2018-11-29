/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:44:03 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/29 10:50:59 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

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

static void print_nm(t_sym *sym, uint32_t space_len) // crap
{
	const char		*zeros = "000000000000000000";
	const char 		*spaces = "                 ";
	unsigned int	x_len;
	unsigned int	arch_len;
	char			c;

	x_len = ft_hex_len(sym->value);
	arch_len = space_len - x_len;
	c = get_type_c(sym);
	//Todo: find cleaner comp
	if (sym->value || c == 't' || c == 'T' || c == 'a' || c == 'A')
	{
		write(1, zeros, arch_len);
		ft_put_ulong_x(sym->value);
	}
	else
		write(1, spaces, space_len);
	ft_putchar(' ');
	ft_putchar(get_type_c(sym));
	ft_putchar(' ');
	ft_putstr(sym->name);
	ft_putchar('\n');
}

static void	print_nm_64(t_sym *sym)
{
	print_nm(sym, 16);
}

static void	print_nm_32(t_sym *sym)
{
	print_nm(sym, 8);
}

//The binary tree has been sorted previously, for no reasons this function has
//to handle the sorting
static void	print_tree(t_sym *curr, bool is_64)
{
	if (curr->right)
		print_tree(curr->right, is_64);
	if (!(curr->type & N_STAB)) //handle otherwise if -a option
	{
		if (is_64)
			print_nm_64(curr);
		else
			print_nm_32(curr);
	}
	if (curr->left)
		print_tree(curr->left, is_64);
}

static void	print_infos(t_print_infos *curr, char *name, enum ftype type, bool multiple)
{
	if (curr)
	{
		// printf("%s(%s)\n", name, curr->name);
		if (type == MH && multiple)
			print_header(name);
		if (type == LIB)
			print_header_lib(name, curr->name);
		if (type == FAT && curr->cputype != CPU_TYPE_X86_64)
			print_header_fat(name, get_archname(curr->cputype, curr->cpusubtype));
			// printf("\n%s(for architecture %s):\n",\
			// name,\
			// get_archname(curr->cputype, curr->cpusubtype));
		print_tree(curr->sym, curr->is_64);
		print_infos(curr->next, name, type, multiple);
	}
}

void		print_file(t_file *f, char *name, bool multiple)
{
	print_infos(f->head, name, f->type, multiple);
}