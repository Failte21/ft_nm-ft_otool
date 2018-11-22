/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:44:03 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/22 10:30:01 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

//This files contains functions to print the symbols previously store in a 
//binary tree of t_sym

//Todo: remove printf
static void	print_nm(t_sym	*sym)
{
	if (sym->value)
		printf("0000000%lx %c %s\n", sym->value, get_type_c(sym->sectname, sym->type), sym->name);
	else
		printf("                 %c %s\n", get_type_c(sym->sectname, sym->type), sym->name);

}

//The binary tree has been sorted previously, for no reasons this function has
//to handle the sorting
static void	print_tree(t_sym *curr)
{
	if (curr->right)
		print_tree(curr->right);
	print_nm(curr);
	if (curr->left)
		print_tree(curr->left);
}

static void	print_infos(t_print_infos *curr, char *name, enum ftype type, bool multiple)
{
	if (curr)
	{
		// printf("%s(%s)\n", name, curr->name);
		if (type == MH && multiple)
			printf("\n%s:\n", name);
		if (type == LIB)
			printf("\n%s(%s):\n", name, curr->name);
		if (type == FAT && curr->cputype != CPU_TYPE_X86_64)
			printf("\n%s(for architecture %s):\n",\
			name,\
			get_archname(curr->cputype, curr->cpusubtype));
		print_tree(curr->sym);
		print_infos(curr->next, name, type, multiple);
	}
}

void		print_file(t_file *f, char *name, bool multiple)
{
	print_infos(f->head, name, f->type, multiple);
}