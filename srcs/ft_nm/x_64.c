/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_64.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:58:08 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/20 17:16:34 by lsimon           ###   ########.fr       */
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
	if (!CHECKED(header, end))
		return (NULL);
	lc = (struct load_command *)(header + 1);
	ncmds = swap ? swap_int32(header->ncmds) : header->ncmds;
	sizeofcmds = swap ? swap_int32(header->sizeofcmds) : header->sizeofcmds;
	if (!CHECKED((struct load_command *)((void *)lc + sizeofcmds), end))
		return (NULL);
	while (ncmds)
	{
		lc = (struct load_command *)((void *)lc + lc->cmdsize);
		if (lc->cmd == LC_SYMTAB) return (struct symtab_command *)lc; //TODO: swap ?
		ncmds--;
	}
	return (NULL);
}
//No idea why it works
static struct section_64	*get_section(struct segment_command_64 *segc, uint32_t i)
{
	struct section_64	*section;

	if (i == NO_SECT)
		return (NULL);
	if (i <= segc->nsects)
	{
		section = (struct section_64 *)(segc + 1);
		i -= 1; // index starts at one
		return (section + i);
	}
	return get_section((struct segment_command_64 *)((void *)segc + segc->cmdsize), i - segc->nsects);
}

static t_sym		*init_sym(struct nlist_64 curr, char *stringable, char segname[16], char sectname[16])
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
		strcpy(new_sym->sectname, sectname);
	return (new_sym);
}

static t_sym		*fill_sym_list(void *ptr, struct nlist_64 *arr, uint32_t nsyms, char *stringable)
{
	t_sym						*head;
	t_sym						*to_insert;
	struct section_64			*section;
	struct segment_command_64	*segc;
	uint32_t					i;

	segc = (struct segment_command_64 *)((struct mach_header_64 *)ptr + 1);
	head = NULL;
	i = 0;
	while (i < nsyms)
	{
		section = get_section(segc, arr[i].n_sect);
		if (!(to_insert = init_sym(
			arr[i],
			stringable, 
			section ? section->segname : NULL,
			section ? section->sectname : NULL
		)))
		{
			//Malloc error
			//Todo: free current tree
			return (NULL);
		}
		head = push_back_tree(head, to_insert);
		i++;
	}
	return (head);
}

t_sym					*get_sym_64(struct symtab_command *sc, void *ptr, void *end)
{
	char						*stringable;
	struct nlist_64				*arr;
	struct segment_command_64	*segc;

	stringable = (char *)ptr + sc->stroff;
	arr = ptr + sc->symoff;
	segc = (struct segment_command_64 *)((struct mach_header_64 *)ptr + 1);
	if (!CHECKED((arr + sc->nsyms - 1), end))
		return (NULL);
	return (fill_sym_list(ptr, arr, sc->nsyms, stringable));
}

static t_print_infos	*get_fat_infos(void *ptr, struct fat_arch_64 *c, uint32_t n, void *end, bool swap)
{
	t_print_infos	*curr;
	uint32_t		offset;

	if (!n)
		return (NULL);
	offset = swap ? swap_int32(c->offset) : c->offset;
	curr = mh_infos(ptr + offset, end);
	curr->next = get_fat_infos(ptr, c + 1, n - 1, end, swap);
	return (curr);
}

t_print_infos			*get_fat_infos_64(void *ptr, void *end, uint32_t n, bool swap)
{
	struct fat_header		*header;
	struct fat_arch_64		*arch;

	header = (struct fat_header *)ptr;
	arch = (struct fat_arch_64 *)(header + 1);
	if (!CHECKED((arch + n), end))
		return (NULL);
	return (get_fat_infos(ptr, arch, n, end, swap)); //recursive is not necessary a good idea here
}