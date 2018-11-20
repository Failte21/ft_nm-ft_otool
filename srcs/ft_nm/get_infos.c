/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:27:37 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/20 11:13:52 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

t_print_infos           *mh_infos(void *ptr, void *end)
{
    uint32_t                magic;
    struct symtab_command   *sc;
    bool                    is_64;
    bool                    swap;
    t_sym                   *sym;

    magic = *(uint32_t *)ptr;
    is_64 = magic == MH_CIGAM_64 || magic == MH_MAGIC_64;
    swap = magic == MH_CIGAM_64 || magic == MH_CIGAM;
    if (!(sc = is_64 ? get_sc_64(ptr, end, swap) : get_sc_32(ptr, end, swap)))
        return (NULL);
    if (!(sym = is_64 ? get_sym_64(sc, ptr, end) : get_sym_32(sc, ptr, end)))
        return (NULL);
    return (NULL);
}

static t_print_infos    *get_macho_infos(void *ptr, void *end)
{
    return (mh_infos(ptr, end));
}

static t_print_infos    *get_fat_infos(void *ptr, void *end)
{
    uint32_t            magic;
    struct fat_header   *header;
    bool                is_swap;
    bool                is_64;
    uint32_t            n;

    magic = *(uint32_t *)ptr;
    is_swap = magic == FAT_CIGAM || magic == FAT_CIGAM_64;
    is_64 = magic == FAT_CIGAM_64 || magic == FAT_MAGIC_64;
    header = ptr;
    n = is_swap ? swap_int32(header->nfat_arch) : header->nfat_arch;
    if (is_64)
        return (get_fat_infos_64(ptr, end, n, is_swap));
    return (get_fat_infos_32(ptr, end, n, is_swap));
}

//Todo: reccursive maybe not a good idea,
//Todo: find a way to clean list junk memory on error
//Todo: x_64 ? x_32 ?
static t_print_infos    *get_lib_infos_lst(void *ptr, void *end, uint32_t i, struct ranlib *curr)
{
    char            *header;
    t_print_infos   *el;
    char            *p;

    if (!i)
        return (NULL);
    header = (char *)ptr + curr->ran_off;
    p = (header + ft_strlen(header));
    while (!(*p))
        p++;
    if (!(el = mh_infos(p, end)))
        return (NULL);
    if (!(el->next = get_lib_infos_lst(ptr, end, i - 1, curr + 1)))
        return (NULL);
    return (el);
}

//TODO: Working but pretty ugly
static t_print_infos    *get_lib_infos(void *ptr, void *end)
{
    int             len;
    uint32_t        size;
    char            *p;
    struct ranlib   *arr;

    len = ft_strlen((char *)ptr);
    p = (ptr + len);
    while (!(*p))
        p++;
    size = *(uint32_t *)p;
    if (!CHECKED(p + size, end)) printf("err");
    arr = (struct ranlib *)((uint32_t *)p + 1);
    return (get_lib_infos_lst(ptr, end, size / sizeof(struct ranlib), arr));
}

t_print_infos	        *get_infos_list(t_file *f)
{
	t_print_infos	*(*get_infos[3])(void *ptr, void *end) = {
		get_macho_infos,
		get_fat_infos,
		get_lib_infos
	};
	return ((*get_infos[f->type])(f->ptr, f->end));
}