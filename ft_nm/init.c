/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:38:36 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/20 15:38:00 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static uint32_t	get_ncmds(t_macho_file macho_file)
{
	struct mach_header_64	*header;

	if (macho_file.is_64)
	{
		header = (struct mach_header_64 *)macho_file.ptr;
		return (header->ncmds);
	} 
	return (0);
}

t_sym			*init_sym(struct nlist_64 curr, char *stringable, char segname[16], char sectname[16])
{
	t_sym	*new_sym;

	if (!(new_sym = (t_sym *)malloc(sizeof(t_sym))))
		return (NULL);
	new_sym->value = curr.n_value;
	new_sym->name = stringable + curr.n_un.n_strx;
	new_sym->type = curr.n_type;
	new_sym->left = NULL;
	new_sym->right = NULL;
	if (segname)
		strcpy(new_sym->segname, segname);
	if (sectname)
		strcpy(new_sym->segname, sectname);
	return (new_sym);
}

t_macho_file	init_macho_file(void *ptr)
{
	uint32_t		magic;
	t_macho_file	macho_file;

	//Get the magic nb and files informations (endian, arch, fat...)
	//Todo: Check for corrupted files
	magic = *(uint32_t *)ptr;
	macho_file.is_64 = magic == MH_MAGIC_64 || magic == MH_CIGAM_64;
	macho_file.is_swap = magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM;
	macho_file.is_fat = magic == FAT_MAGIC || magic == FAT_CIGAM;
	macho_file.ptr = ptr;

	macho_file.ncmds = get_ncmds(macho_file);
	return macho_file;
}