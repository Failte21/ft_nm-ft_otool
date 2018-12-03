/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_64.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:58:08 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/03 09:58:21 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

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

static struct section_64	*get_text_section(struct segment_command_64 *segc, bool swap)
{
	struct section_64	*section;
	uint32_t			nsects;
	unsigned int		i;

	section = (struct section_64 *)(segc + 1);
	nsects = swap ? swap_int32(segc->nsects) : segc->nsects;
	if (!ft_strcmp(section->segname, SEG_TEXT))
	{
		i = 0;
		while (i < nsects)
		{
			if (!ft_strcmp(section[i].sectname, SECT_TEXT))
				return (section + i);
			i++;
		}
		return (NULL);
	}
	//todo: stop at some point 
	return get_text_section((struct segment_command_64 *)((void *)segc + segc->cmdsize), swap);
}

t_hex_dump					*get_hex_dump_64(void *ptr, void *end)
{
	struct segment_command_64	*segc;
	struct section_64			*sec;
	char						*datas;
	uint64_t					i;

	if (!end)
		return (NULL); //TODO: undo
	segc = (struct segment_command_64 *)((struct mach_header_64 *)ptr + 1);
	sec = get_text_section(segc, false); //TODO: unmock endian
	datas = (char *)(ptr + sec->offset);
	i = 0;
	while (i < sec->size)
	{
		// printf("%02X ", datas[i]);
		ft_put_hex_precision(datas[i], 2);
		ft_putchar(' ');
		i++;
	}
	// printf("%s\n, %s\n, %llX\n, %d\n", sec->segname, sec->sectname, sec->addr, *((uint32_t *)(ptr + sec->addr)));
	return (NULL);
}