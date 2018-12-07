/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:44:03 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/07 09:28:12 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

static void	print_nm(t_sym *sym, uint32_t space_len)
{
	const char		*zeros = "000000000000000000";
	const char		*spaces = "                 ";
	unsigned int	x_len;
	unsigned int	arch_len;
	char			c;

	x_len = ft_hex_len(sym->value);
	arch_len = space_len - x_len;
	c = get_type_c(sym);
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

static void	print_tree(t_sym *curr, bool is_64)
{
	if (curr->right)
		print_tree(curr->right, is_64);
	if (!(curr->type & N_STAB))
	{
		if (is_64)
			print_nm(curr, 16);
		else
			print_nm(curr, 8);
	}
	if (curr->left)
		print_tree(curr->left, is_64);
}

static int	print_infos(t_print_infos *curr,\
	char *name, enum ftype type, bool multiple)
{
	int	err;

	err = 0;
	if (curr)
	{
		print_header(type, multiple, name, curr);
		if (curr->failed)
		{
			ft_putstr_fd("An error occured\n", 2);
			err++;
		}
		else
			print_tree(curr->sym, curr->is_64);
		print_infos(curr->next, name, type, multiple);
	}
	return (err);
}

int			print_file(t_file *f, char *name, bool multiple)
{
	return (print_infos(f->head, name, f->type, multiple));
}
