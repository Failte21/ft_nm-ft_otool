/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_64.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:58:08 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/20 13:11:35 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

struct symtab_command	*get_sc_64(void *ptr, uint32_t ncmds)
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

t_sym					*get_symbols_64(char *stringable, uint32_t nsyms, uint32_t symoff, void *ptr)
{
	t_sym			*head;
	t_sym			*to_insert;
	struct 			nlist_64	*arr;
	uint32_t		i;

	i = 0;
	head = NULL;
	arr = (struct nlist_64 *)(ptr + symoff);
	while (i < nsyms)
	{
		to_insert = init_sym(arr[i], stringable);
		head = push_back_tree(head, to_insert);
		i++;
	}
	return (head);
}