/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_64.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:58:08 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/07 13:06:29 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

static struct section_64	*get_text_section(struct segment_command_64 *segc,\
												bool swap, void *end)
{
	struct section_64	*section;
	uint32_t			nsects;
	uint32_t			cmdsize;
	unsigned int		i;

	if (!CHECKED(segc, end))
		return (handle_error_null("Truncated segment command\n"));
	cmdsize = swap ? swap_int32(segc->cmdsize) : segc->cmdsize;
	section = (struct section_64 *)(segc + 1);
	nsects = swap ? swap_int32(segc->nsects) : segc->nsects;
	if (!CHECKED(section + nsects, end))
		return (handle_error_null("Truncated sections\n"));
	if (!ft_strncmp(section->segname, SEG_TEXT, 16))
	{
		i = 0;
		while (i < nsects)
		{
			if (!ft_strncmp(section[i].sectname, SECT_TEXT, 16))
				return (section + i);
			i++;
		}
		return (handle_error_null("Missing section __Text, __text\n"));
	}
	return (get_text_section((struct segment_command_64 *)\
				((void *)segc + cmdsize), swap, end));
}

static t_hex_dump			*init_hex_dump(struct section_64 *sec,\
									void *ptr, void *end)
{
	char		*datas;
	t_hex_dump	*hd;

	datas = (char *)(ptr + sec->offset);
	if (!CHECKED(datas + sec->size, end))
		return (handle_error_null("Truncated datas\n"));
	if (!(hd = (t_hex_dump *)malloc(sizeof(t_hex_dump))))
		return (handle_error_null("Mallloc error\n"));
	hd->datas = datas;
	hd->sec64 = sec;
	return (hd);
}

t_hex_dump					*get_hex_dump_64(void *ptr, void *end, bool swap)
{
	struct segment_command_64	*segc;
	struct section_64			*sec;
	struct mach_header_64		*header;
	void						*endlc;

	header = (struct mach_header_64 *)ptr;
	if (swap)
		sw_mach_header_64(header);
	segc = (struct segment_command_64 *)(header + 1);
	endlc = (void *)segc + header->sizeofcmds;
	if (endlc > end)
		return (handle_error_null("Truncated load commands\n"));
	if (!(sec = get_text_section(segc, swap, end)))
		return (NULL);
	return (init_hex_dump(sec, ptr, end));
}
