/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_32.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:58:08 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/06 13:08:35 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

static struct section	*get_text_section(struct segment_command *segc, bool swap, void *end)
{
	struct section	*section;
	uint32_t		nsects;
	uint32_t		cmdsize;
	unsigned int	i;


	if (!CHECKED(segc, end)) 
		return (NULL);
	cmdsize = swap ? swap_int32(segc->cmdsize) : segc->cmdsize;
	nsects = swap ? swap_int32(segc->nsects) : segc->nsects;
	section = (struct section *)(segc + 1);
	if (!CHECKED(section + nsects, end)) 
		return (NULL);
	if (!ft_strncmp(section->segname, SEG_TEXT, 16))
	{
		i = 0;
		while (i < nsects)
		{
			if (!ft_strncmp(section[i].sectname, SECT_TEXT, 16))
				return (section + i);
			i++;
		}
		return (NULL);
	}
	return get_text_section((struct segment_command *)((void *)segc + cmdsize), swap, end);
}

static t_hex_dump			*init_hex_dump(struct section *sec, void *ptr, void *end)
{
	char		*datas;
	t_hex_dump	*hd;
	datas = (char *)(ptr + sec->offset);
	if (!CHECKED(datas + sec->size, end))
		return (NULL);
	if (!(hd = (t_hex_dump *)malloc(sizeof(t_hex_dump))))
		return (NULL);
	hd->datas = datas;
	hd->sec32 = sec;
	return (hd);
}

t_hex_dump					*get_hex_dump_32(void *ptr, void *end, bool swap)
{
	struct segment_command	*segc;
	struct section			*sec;
	struct mach_header		*header;
	void					*endlc;

	header = (struct mach_header *)ptr;
	if (swap)
		sw_mach_header_32(header);
	segc = (struct segment_command *)(header + 1);
	endlc = (void *)segc + header->sizeofcmds;

	if (endlc > end)
		return (NULL);
	if (!(sec = get_text_section(segc, swap, endlc)))
		return (NULL);
	if (swap)
		sw_section_32(sec);
	return (init_hex_dump(sec, ptr, end));
}