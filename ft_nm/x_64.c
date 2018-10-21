/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_64.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:58:08 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/21 12:07:50 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

struct symtab_command		*get_sc_64(void *ptr, uint32_t ncmds)
{
	uint32_t					i;
	struct load_command			*lc;

	lc = (struct load_command *)((struct mach_header_64 *)ptr + 1);
	i = 0;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			return (struct symtab_command *)lc;
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	return NULL;
}

//This function wasn't really tested and might cause some bugs later
static struct section_64	*get_section_64(struct segment_command_64 *sc, uint32_t i)
{
	struct section_64	*section;

	if (i == NO_SECT)
		return (NULL);
	if (i <= sc->nsects)
	{
		section = (struct section_64 *)(sc + 1);
		i -= 1; // index starts at one
		return (section + i);
	}
	return get_section_64((struct segment_command_64 *)((void *)sc + sc->cmdsize), i - sc->nsects);
}

t_sym						*get_symbols_64(char *stringable, uint32_t nsyms, uint32_t symoff, void *ptr)
{
	t_sym						*head;
	struct segment_command_64	*sc;
	struct section_64			*section;
	t_sym						*to_insert;
	struct 						nlist_64	*arr;
	uint32_t					i;

	i = 0;
	head = NULL;
	arr = (struct nlist_64 *)(ptr + symoff);
	while (i < nsyms)
	{
		sc = (struct segment_command_64 *)((struct mach_header_64 *)ptr + 1);
		section = get_section_64(sc, arr[i].n_sect);
		to_insert = init_sym(
			arr[i], 
			stringable, 
			section ? section->segname : NULL,
			section ? section->sectname : NULL
		);
		head = push_back_tree(head, to_insert);
		i++;
	}
	return (head);
}