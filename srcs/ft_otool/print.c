/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:44:03 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/07 11:00:06 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

static void	print_dump(t_print_infos *curr)
{
	ft_putstr("Contents of (__TEXT,__text) section\n");
	if (curr->cputype == CPU_TYPE_I386 || curr->cputype == CPU_TYPE_X86_64)
	{
		if (curr->is_64)
			print_dump_64_space(curr->hex_dump);
		else
			print_dump_32_space(curr->hex_dump);
	}
	else
	{
		if (curr->is_64)
			print_dump_64_block(curr->hex_dump, curr->swap);
		else
			print_dump_32_block(curr->hex_dump, curr->swap);
	}
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
		else
			print_dump(curr);
		err += print_infos(curr->next, name, type);
	}
	return (err);
}

int			print_file(t_file *f, char *name)
{
	if (f->type == LIB)
	{
		ft_putstr("Archive : ");
		ft_putstr(name);
		ft_putchar('\n');
	}
	return (print_infos(f->head, name, f->type));
}
