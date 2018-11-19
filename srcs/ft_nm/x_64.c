/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_64.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:58:08 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/19 18:05:27 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

struct symtab_command		*get_sc_64(void *ptr, void *end, bool swap)
{
	struct load_command		*lc;
	struct mach_header_64		*header;
	uint32_t				ncmds;
	uint32_t				sizeofcmds;

	header = (struct mach_header_64 *)ptr;
	if (!CHECKED(header, end)) printf("err");
	lc = (struct load_command *)(header + 1);
	ncmds = swap ? swap_int32(header->ncmds) : header->ncmds;
	sizeofcmds = swap ? swap_int32(header->sizeofcmds) : header->sizeofcmds;
	if (!CHECKED((struct load_command *)((void *)lc + sizeofcmds), end)) printf("err");
	while (ncmds)
	{
		lc = (struct load_command *)((void *)lc + lc->cmdsize);
		if (lc->cmd == LC_SYMTAB) return (struct symtab_command *)lc; //TODO: swap ?
		ncmds--;
	}
	return (NULL);
}

// //This function wasn't really tested and might cause some bugs later
// static struct section_64	*get_section_64(struct segment_command_64 *sc, uint32_t i, t_macho_file *mf)
// {
// 	struct section_64	*section;
// 	size_t				seg_size;

// 	if (i == NO_SECT)
// 		return (NULL);
// 	if (i <= sc->nsects)
// 	{
// 		seg_size = sizeof(struct segment_command_64);
// 		if (!(section = (struct section_64 *)get_ptr(mf, sc, seg_size, seg_size)))
// 			return (NULL);
// 		i -= 1; // index starts at one
// 		return (section + i);
// 	}
// 	return get_section_64((struct segment_command_64 *)((void *)sc + sc->cmdsize), i - sc->nsects, mf);
// }

// t_sym						*get_symbols_64(char *stringable, uint32_t nsyms, uint32_t symoff, t_macho_file *mf)
// {
// 	t_sym						*head;
// 	struct segment_command_64	*sc;
// 	struct section_64			*section;
// 	t_sym						*to_insert;
// 	struct nlist_64				*arr;
// 	uint32_t					i;
// 	size_t						header_size;
// 	size_t						struct_size;
// 	void						*tmp;

// 	i = 0;
// 	head = NULL;
// 	if (!(arr = get_ptr(mf, mf->ptr, symoff, sizeof(struct nlist_64))))
// 		return (NULL);
// 	header_size = sizeof(struct mach_header_64);
// 	struct_size = sizeof(struct segment_command_64);
// 	while (i < nsyms)
// 	{
// 		if (!(sc = (struct segment_command_64 *)get_ptr(mf, mf->ptr, header_size, struct_size)))
// 			return (NULL);
// 		section = get_section_64(sc, arr[i].n_sect, mf);
// 		if (!(tmp = get_ptr(mf, (void *)arr, sizeof(struct nlist_64) * i, sizeof(struct nlist_64))))
// 			return (NULL);
// 		to_insert = init_sym(
// 			tmp,
// 			stringable, 
// 			section ? section->segname : NULL,
// 			section ? section->sectname : NULL
// 		);
// 		head = push_back_tree(head, to_insert);
// 		i++;
// 	}
// 	return (head);
// }

t_print_infos			*mh_infos_64(void *ptr, bool swap, void *end)
{
	struct mach_header_64	*header;

	header = ptr;
	if (!CHECKED(header, end)) return (NULL);
	//TODO swap
	if (swap)
		return (NULL);
	return (NULL);
}

static t_print_infos	*get_fat_infos(void *ptr, struct fat_arch_64 *c, uint32_t n, void *end, bool swap)
{
	t_print_infos	*curr;
	uint32_t		offset;

	if (!n)
		return (NULL);
	offset = swap ? swap_int32(c->offset) : c->offset;
	curr = mh_infos(ptr + c->offset, end);
	curr->next = get_fat_infos(ptr, c + 1, n - 1, end, swap);
	return (curr);
}

t_print_infos			*get_fat_infos_64(void *ptr, void *end, uint32_t n, bool swap)
{
	struct fat_header	*header;
	struct fat_arch_64	*arch;

	header = (struct fat_header *)ptr;
	arch = (struct fat_arch_64 *)header + 1;
	if (!CHECKED((arch + n), end)) return (NULL);
	return (get_fat_infos(ptr, arch, n, end, swap)); //recursive is not necessary a good idea here
}