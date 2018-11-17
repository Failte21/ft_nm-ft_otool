/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_64.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:58:08 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/17 14:16:39 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

struct symtab_command		*get_sc_64(t_macho_file *mf)
{
	uint32_t				i;
	struct load_command		*lc;
	size_t					header_size;

	header_size = sizeof(struct mach_header_64);
	if (!(lc = (struct load_command *)get_ptr(mf, mf->ptr, header_size, header_size)))
		return (NULL);
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
	void						*tmp;

	i = 0;
	head = NULL;
	if (!(arr = get_ptr(mf, mf->ptr, symoff, sizeof(struct nlist_64))))
		return (NULL);
	header_size = sizeof(struct mach_header_64);
	struct_size = sizeof(struct segment_command_64);
	while (i < nsyms)
	{
		if (!(sc = (struct segment_command_64 *)get_ptr(mf, mf->ptr, header_size, struct_size)))
			return (NULL);
		section = get_section_64(sc, arr[i].n_sect, mf);
		if (!(tmp = get_ptr(mf, (void *)arr, sizeof(struct nlist_64) * i, sizeof(struct nlist_64))))
			return (NULL);
		to_insert = init_sym(
			tmp,
			stringable, 
			section ? section->segname : NULL,
			section ? section->sectname : NULL
		);
		head = push_back_tree(head, to_insert);
		i++;
	}
	return (head);
}