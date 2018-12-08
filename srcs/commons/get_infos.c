/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:27:37 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/08 10:14:01 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commons.h"

static t_print_infos	*get_macho_infos(t_file *f)
{
	return (mh_infos(f->ptr, f->end));
}

static t_print_infos	*get_fat_infos(t_file *f)
{
	uint32_t			magic;
	struct fat_header	*header;
	bool				is_swap;
	bool				is_64;
	uint32_t			n;

	magic = *(uint32_t *)f->ptr;
	is_swap = magic == FAT_CIGAM || magic == FAT_CIGAM_64;
	is_64 = magic == FAT_CIGAM_64 || magic == FAT_MAGIC_64;
	header = (struct fat_header *)f->ptr;
	n = is_swap ? swap_int32(header->nfat_arch) : header->nfat_arch;
	if (is_64)
		return (get_fat_infos_64(f, n, is_swap));
	return (get_fat_infos_32(f, n, is_swap));
}

t_print_infos			*get_infos_list(t_file *f)
{
	static t_print_infos	*(*get_infos[3])(t_file *f) = {
		get_macho_infos,
		get_fat_infos,
		get_lib_infos
	};

	return ((*get_infos[f->type])(f));
}

t_file					*get_infos(char *name)
{
	t_file	*f;

	if (!(f = init_file(name)))
		return (NULL);
	return (f);
}
