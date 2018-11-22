/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:04:04 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/22 13:47:25 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commons.h"

void    sw_mach_header_32(struct mach_header *h)
{
	// h->cputype = ?; swap ?
	// h->cpusubtype = ?; swap ?
	h->filetype = swap_int32(h->filetype);
	h->ncmds = swap_int32(h->ncmds);
	h->sizeofcmds = swap_int32(h->sizeofcmds);
	h->flags = swap_int32(h->flags);		
}

void    sw_segment_command_32(struct segment_command *sc)
{
	sc->cmd = swap_int32(sc->cmd);
	sc->cmdsize = swap_int32(sc->cmdsize);
	// sc->segname = ?; //swap ?
	sc->vmaddr = swap_int64(sc->vmaddr);
	sc->vmsize = swap_int64(sc->vmsize);
	sc->fileoff = swap_int64(sc->fileoff);
	sc->filesize = swap_int64(sc->filesize);
	// sc->maxprot = ?; //swap ?
	// sc->initprot = ?; //swap ?
	sc->nsects = swap_int32(sc->nsects);
	sc->flags = swap_int32(sc->flags);
};

void sw_section_32(struct section *section)
{
	// section->sectname = ? // swap ?;
	// section->segname = ? // swap ?;
	section->addr = swap_int32(section->addr);
	section->size = swap_int32(section->size);
	section->offset = swap_int32(section->offset);
	section->align = swap_int32(section->align);
	section->reloff = swap_int32(section->reloff);
	section->nreloc = swap_int32(section->nreloc);
	section->flags = swap_int32(section->flags);
	section->reserved1 = swap_int32(section->reserved1);
	section->reserved2 = swap_int32(section->reserved2);
};

void sw_arch_32(struct fat_arch *arch)
{
	arch->cputype = swap_int32(arch->cputype);
	arch->cpusubtype = swap_int32(arch->cpusubtype);
	arch->offset = swap_int32(arch->offset);
	arch->size = swap_int32(arch->size);
	arch->align = swap_int32(arch->align);
};

static void sw_nlist(struct nlist *nl)
{
	nl->n_un.n_strx = swap_int32(nl->n_un.n_strx);
	// nl->n_type = ? // swap ?;
	// nl->n_sect = ? // swap ?;
    // nl->n_desc = ? // swap ?;
	nl->n_value = swap_int32(nl->n_value);
};

void sw_nlist_32(struct nlist *nl, uint32_t nsyms)
{
    uint32_t    i;

    i = 0;
    while (i < nsyms)
    {
        sw_nlist(nl + i);
        i++;
    }
}