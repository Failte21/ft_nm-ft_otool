/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_32.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:58:08 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/19 18:04:30 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

struct symtab_command		*get_sc_32(void *ptr, void *end, bool swap)
{
	struct load_command		*lc;
	struct mach_header		*header;
	uint32_t				ncmds;
	uint32_t				sizeofcmds;

	header = (struct mach_header *)ptr;
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

// t_print_infos		*mh_infos_32(void *ptr, bool swap, void *end)
// {
// 	struct mach_header		*header;
// 	struct symtab_command	*sc;

// 	header = ptr;
// 	if (!CHECKED(header, end)) return (NULL);
// 	//TODO swap
// 	if (swap)
// 		return (NULL);
// 	return (NULL);
// }

static t_print_infos	*get_fat_infos(void *ptr, struct fat_arch *c, uint32_t n, void *end, bool swap)
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

t_print_infos			*get_fat_infos_32(void *ptr, void *end, uint32_t n, bool swap)
{
	struct fat_header	*header;
	struct fat_arch	*arch;

	header = (struct fat_header *)ptr;
	arch = (struct fat_arch *)(header + 1);
	// if (!CHECKED((arch + n), end))return (NULL);
	return (get_fat_infos(ptr, arch, n, end, swap)); //recursive is not necessary a good idea here
}