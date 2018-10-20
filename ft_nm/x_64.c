/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_64.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:58:08 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/20 13:46:23 by lsimon           ###   ########.fr       */
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

struct segment_command_64	*get_segment_64(void *ptr, uint32_t i)
{
	struct segment_command_64	*arr;

	arr = (struct segment_command_64 *)((struct mach_header_64 *)ptr + 1);
	if (i == NO_SECT)
		return (NULL);
	return (arr + i);
}

t_sym						*get_symbols_64(char *stringable, uint32_t nsyms, uint32_t symoff, void *ptr)
{
	t_sym						*head;
	struct segment_command_64	*sc;
	t_sym						*to_insert;
	struct 						nlist_64	*arr;
	uint32_t					i;

	i = 0;
	head = NULL;
	arr = (struct nlist_64 *)(ptr + symoff);
	while (i < nsyms)
	{
		sc = get_segment_64(ptr, arr[i].n_sect);
		to_insert = init_sym(arr[i], stringable, sc ? sc->segname : NULL);
		head = push_back_tree(head, to_insert);
		i++;
	}
	return (head);
}