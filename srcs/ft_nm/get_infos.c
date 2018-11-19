/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:27:37 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/19 15:02:45 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

static t_mh    *get_macho_infos(t_file *f, void *ptr)
{
    t_mh    *infos;

    if (!(infos = init_infos(ptr)))
        return (NULL);
}

static t_mh    *get_fat_infos(t_file *f, void *ptr)
{
    t_mh       *head;
    uint32_t            magic;
    bool                is_swap;

    magic = *(uint32_t *)ptr;
    is_swap = magic == FAT_CIGAM || magic == FAT_CIGAM_64;
    if (magic == FAT_CIGAM_64 || magic == FAT_MAGIC_64)
        return (get_fat_infos_64(ptr, is_swap));
    //TODO 32
    // return (get_fat_infos_32(ptr, is_swap));
    return (NULL);
}

static t_mh    *get_lib_infos(t_file *f, void *ptr)
{
    return (t_mh *)(f->ptr - ptr);
}

t_mh	        *get_infos_list(t_file *f)
{
	t_mh	*(*get_infos[3])(t_file *f, void *ptr) = {
		get_macho_infos,
		get_fat_infos,
		get_lib_infos
	};
	return ((*get_infos[f->type])(f, f->ptr));
}