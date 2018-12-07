/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sym32.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:58:08 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/07 10:27:59 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

static t_sym				*init_sym(struct nlist curr, char *stringable,\
									struct section *s, char *strend)
{
	t_sym	*new_sym;
	char	*name;

	if (!(new_sym = (t_sym *)malloc(sizeof(t_sym))))
		return (handle_error_null("Malloc error\n"));
	name = stringable + curr.n_un.n_strx;
	if (!CHECKED(name, strend))
		return (handle_error_null("Bad string index\n"));
	new_sym->value = curr.n_value;
	new_sym->name = name;
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

static struct section		*get_section(struct segment_command *segc,\
										uint32_t i, bool swap)
{
	struct section	*section;
	uint32_t		nsects;

	if (i == NO_SECT)
		return (NULL);
	nsects = swap ? swap_int32(segc->nsects) : segc->nsects;
	if (i <= nsects)
	{
		section = (struct section *)(segc + 1);
		i -= 1;
		return (section + i);
	}
	return (get_section(\
		(struct segment_command *)((void *)segc + segc->cmdsize),\
		i - nsects, swap));
}

static t_sym				*fill_sym_list(void *ptr, t_sym_r sr,\
							bool swap, char *strend)
{
	t_sym					*head;
	t_sym					*to_insert;
	struct section			*section;
	struct segment_command	*segc;
	uint32_t				i;

	segc = (struct segment_command *)((struct mach_header *)ptr + 1);
	head = NULL;
	i = 0;
	while (i < sr.nsyms)
	{
		section = get_section(segc, sr.arr[i].n_sect, swap);
		if (!(to_insert =\
			init_sym(sr.arr[i], sr.stringable, section, strend)))
		{
			free_tree(head);
			return (NULL);
		}
		head = push_back_tree(head, to_insert);
		i++;
	}
	return (head);
}

t_sym						*get_sym_32(struct symtab_command *sc,\
								void *ptr, void *end, bool swap)
{
	struct segment_command	*segc;
	char					*strend;
	t_sym_r					sr;

	sr.stringable = (char *)ptr + sc->stroff;
	strend = (char *)ptr + sc->stroff + sc->strsize;
	sr.arr = ptr + sc->symoff;
	segc = (struct segment_command *)((struct mach_header *)ptr + 1);
	if (!CHECKED(&(sr.arr[sc->nsyms]), end))
		return (handle_error_null("Truncated string table\n"));
	if (swap)
		sw_nlist_32(sr.arr, sc->nsyms);
	sr.nsyms = sc->nsyms;
	return (fill_sym_list(ptr, sr, swap, strend));
}
