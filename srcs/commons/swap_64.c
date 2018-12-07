/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 10:59:26 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/07 14:53:04 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commons.h"

void    sw_mach_header_64(struct mach_header_64 *h)
{
	h->filetype = swap_int32(h->filetype);
	h->ncmds = swap_int32(h->ncmds);
	h->sizeofcmds = swap_int32(h->sizeofcmds);
	h->flags = swap_int32(h->flags);		
	h->reserved = swap_int32(h->reserved);
}

void    sw_segment_command_64(struct segment_command_64 *sc)
{
	sc->cmd = swap_int32(sc->cmd);
	sc->cmdsize = swap_int32(sc->cmdsize);
	sc->vmaddr = swap_int64(sc->vmaddr);
	sc->vmsize = swap_int64(sc->vmsize);
	sc->fileoff = swap_int64(sc->fileoff);
	sc->filesize = swap_int64(sc->filesize);
	sc->nsects = swap_int32(sc->nsects);
	sc->flags = swap_int32(sc->flags);
};

void sw_section_64(struct section_64 *section)
{
	section->addr = swap_int64(section->addr);
	section->size = swap_int64(section->size);
	section->offset = swap_int64(section->offset);
	section->align = swap_int64(section->align);
	section->reloff = swap_int64(section->reloff);
	section->nreloc = swap_int64(section->nreloc);
	section->flags = swap_int64(section->flags);
	section->reserved1 = swap_int64(section->reserved1);
	section->reserved2 = swap_int64(section->reserved2);
};

void sw_arch_64(struct fat_arch_64 *arch)
{
	arch->cputype = swap_int64(arch->cputype);
	arch->cpusubtype = swap_int64(arch->cpusubtype);
	arch->offset = swap_int64(arch->offset);
	arch->size = swap_int64(arch->size);
	arch->align = swap_int32(arch->align);
	arch->reserved = swap_int32(arch->reserved);
};