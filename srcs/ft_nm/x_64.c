/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_64.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:58:08 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/17 13:53:10 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

struct symtab_command		*get_sc_64(t_macho_file *mf)
{
	uint32_t				i;
	struct load_command		*lc;
	size_t					header_size;

	header_size = sizeof(struct mach_header_64);
	lc = (struct load_command *)get_ptr(mf, mf->ptr, header_size, header_size);
	i = 0;
	while (i < mf->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			return (struct symtab_command *)lc;
		if (!(lc = get_ptr(mf, lc, lc->cmdsize, sizeof(struct load_command))))
			return (NULL);
		i++;
	}
	return (NULL);
}

//This function wasn't really tested and might cause some bugs later
static struct section_64	*get_section_64(struct segment_command_64 *sc, uint32_t i, t_macho_file *mf)
{
	struct section_64	*section;
	size_t				seg_size;

	if (i == NO_SECT)
		return (NULL);
	if (i <= sc->nsects)
	{
		seg_size = sizeof(struct segment_command_64);
		if (!(section = (struct section_64 *)get_ptr(mf, sc, seg_size, seg_size)))
			return (NULL);
		i -= 1; // index starts at one
		return (section + i);
	}
	return get_section_64((struct segment_command_64 *)((void *)sc + sc->cmdsize), i - sc->nsects, mf);
}

t_sym						*get_symbols_64(char *stringable, uint32_t nsyms, uint32_t symoff, t_macho_file *mf)
{
	t_sym						*head;
	struct segment_command_64	*sc;
	struct section_64			*section;
	t_sym						*to_insert;
	struct nlist_64				*arr;
	uint32_t					i;
	size_t						header_size;
	size_t						struct_size;

	i = 0;
	head = NULL;
	arr = get_ptr(mf, mf->ptr, symoff, sizeof(struct nlist_64));
	header_size = sizeof(struct mach_header_64);
	struct_size = sizeof(struct segment_command_64);
	while (i < nsyms)
	{
		sc = (struct segment_command_64 *)get_ptr(mf, mf->ptr, header_size, struct_size);
		section = get_section_64(sc, arr[i].n_sect, mf);
		//protected add somehow not working
		to_insert = init_sym(
			(void *)arr + sizeof(struct nlist_64) * i,
			// get_ptr(mf, (void *)arr, sizeof(struct nlist_64) * i, sizeof(struct nlist_64)),
			stringable, 
			section ? section->segname : NULL,
			section ? section->sectname : NULL
		);
		head = push_back_tree(head, to_insert);
		i++;
	}
	return (head);
}