/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symtab_cmd64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 10:27:22 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/07 10:52:53 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

static struct load_command	*get_lc(struct mach_header_64 *h,\
									void *end, bool swap)
{
	struct load_command		*lc;

	if (!CHECKED(h, end))
		return (handle_error_null("Truncated file\n"));
	if (swap)
		sw_mach_header_64(h);
	lc = (struct load_command *)(h + 1);
	if (!CHECKED((struct load_command *)((void *)lc + h->sizeofcmds), end))
		return (handle_error_null("Truncated load commands\n"));
	if (swap)
		sw_load_command(lc);
	return (lc);
}

struct symtab_command		*get_sc_64(void *ptr, void *end, bool swap)
{
	struct load_command		*lc;
	struct mach_header_64	*header;
	uint32_t				ncmds;

	header = (struct mach_header_64 *)ptr;
	if (!(lc = get_lc(header, end, swap)))
		return (NULL);
	ncmds = header->ncmds;
	while (ncmds)
	{
		lc = (struct load_command *)((void *)lc + lc->cmdsize);
		if (!CHECKED(lc, end))
			return (handle_error_null("Truncated load commands\n"));
		if (swap)
			sw_load_command(lc);
		if (lc->cmd == LC_SYMTAB)
			return (struct symtab_command *)lc;
		ncmds--;
	}
	return (handle_error_null("Symtab command is missing\n"));
}
