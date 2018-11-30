/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_64.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:58:08 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/30 13:05:07 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

struct symtab_command		*get_sc_64(void *ptr, void *end, bool swap)
{
	struct load_command		*lc;
	struct mach_header_64		*header;
	uint32_t				ncmds;

	header = (struct mach_header_64 *)ptr;
	if (swap)
		sw_mach_header_64(header);
	if (!CHECKED(header, end))
		return (NULL);
	lc = (struct load_command *)(header + 1);
	if (!CHECKED((struct load_command *)((void *)lc + header->sizeofcmds), end))
		return (NULL);
	if (swap)
		sw_load_command(lc);
	ncmds = header->ncmds;
	while (ncmds)
	{
		lc = (struct load_command *)((void *)lc + lc->cmdsize);
		if (!CHECKED(lc ,end))
			return (NULL);
		if (swap)
			sw_load_command(lc);
		if (lc->cmd == LC_SYMTAB)
			return (struct symtab_command *)lc;
		ncmds--;
	}
	return (NULL);
}

static t_sym		*init_sym(struct nlist_64 curr, char *stringable, struct section_64 *s, void *end)
{
	t_sym	*new_sym;
	char	*name;

	if (!(new_sym = (t_sym *)malloc(sizeof(t_sym))))
		return (NULL);
	name = stringable + curr.n_un.n_strx;
	new_sym->value = curr.n_value;
	new_sym->name = name > (char *)end ? BAD_INDEX_STR : name;
	new_sym->n_sect = curr.n_sect;
	new_sym->type = curr.n_type;
	new_sym->left = NULL;
	new_sym->right = NULL;
	if (s)
	{
		ft_strcpy(new_sym->segname, s->segname);
		ft_strcpy(new_sym->sectname, s->sectname);
	}
	return (new_sym);
}

static struct section_64	*get_section(struct segment_command_64 *segc, uint32_t i, bool swap)
{
	struct section_64	*section;
	uint32_t			nsects;

	if (i == NO_SECT)
		return (NULL);
	nsects = swap ? swap_int32(segc->nsects) : segc->nsects;
	if (i <= nsects)
	{
		section = (struct section_64 *)(segc + 1);
		i -= 1; // index starts at one
		return (section + i);
	}
	return get_section((struct segment_command_64 *)((void *)segc + segc->cmdsize), i - nsects, swap);
}

static t_sym		*fill_sym_list(void *ptr, struct nlist_64 *arr, uint32_t nsyms, char *stringable, bool swap, void *end)
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
		section = get_section(segc, arr[i].n_sect, swap);
		if (!(to_insert = init_sym(
			arr[i],
			stringable, 
			section ? section : NULL,
			end
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

t_sym					*get_sym_64(struct symtab_command *sc, void *ptr, void *end, bool swap)
{
	char						*stringable;
	struct nlist_64				*arr;
	struct segment_command_64	*segc;

	stringable = (char *)ptr + sc->stroff;
	arr = ptr + sc->symoff;
	segc = (struct segment_command_64 *)((struct mach_header_64 *)ptr + 1);
	if (!CHECKED((arr + sc->nsyms - 1), end))
		return (NULL);
	if (swap)
		sw_nlist_64(arr, sc->nsyms);
	return (fill_sym_list(ptr, arr, sc->nsyms, stringable, swap, end));
}