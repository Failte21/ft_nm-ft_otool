/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:04:04 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/08 13:11:28 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commons.h"

void	sw_mach_header_32(struct mach_header *h)
{
	h->filetype = swap_int32(h->filetype);
	h->ncmds = swap_int32(h->ncmds);
	h->sizeofcmds = swap_int32(h->sizeofcmds);
	h->flags = swap_int32(h->flags);
}

void	sw_segment_command_32(struct segment_command *sc)
{
	sc->cmd = swap_int32(sc->cmd);
	sc->cmdsize = swap_int32(sc->cmdsize);
	sc->vmaddr = swap_int64(sc->vmaddr);
	sc->vmsize = swap_int64(sc->vmsize);
	sc->fileoff = swap_int64(sc->fileoff);
	sc->filesize = swap_int64(sc->filesize);
	sc->nsects = swap_int32(sc->nsects);
	sc->flags = swap_int32(sc->flags);
}

void	sw_section_32(struct section *section)
{
	section->addr = swap_int32(section->addr);
	section->size = swap_int32(section->size);
	section->offset = swap_int32(section->offset);
	section->align = swap_int32(section->align);
	section->reloff = swap_int32(section->reloff);
	section->nreloc = swap_int32(section->nreloc);
	section->flags = swap_int32(section->flags);
	section->reserved1 = swap_int32(section->reserved1);
	section->reserved2 = swap_int32(section->reserved2);
}

void	sw_arch_32(struct fat_arch *arch)
{
	arch->cputype = swap_int32(arch->cputype);
	arch->cpusubtype = swap_int32(arch->cpusubtype);
	arch->offset = swap_int32(arch->offset);
	arch->size = swap_int32(arch->size);
	arch->align = swap_int32(arch->align);
}
