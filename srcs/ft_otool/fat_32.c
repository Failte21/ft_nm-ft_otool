/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_32.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 09:16:10 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/03 08:04:43 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

static t_print_infos        *get_fat_macho(t_file *f, struct fat_arch *c, bool swap)
{
	t_print_infos	*curr;

	if (swap)
		sw_arch_32(c);
	curr = mh_infos(f->ptr + c->offset, f->end);
	curr->cputype = c->cputype;
	curr->cpusubtype = c->cpusubtype;
	return (curr);
}

static struct fat_arch   *get_host_arch(void *ptr, struct fat_arch *c, uint32_t n, void *end, bool swap)
{
	cpu_type_t  cpu_type;

	if (!n)
		return (NULL);
	cpu_type = swap ? swap_int32(c->cputype) : c->cputype;
    if (cpu_type != CPU_TYPE_X86_64)
        return (get_host_arch(ptr, c + 1, n - 1, end, swap));
    return (c);
}

static t_print_infos	    *get_fat_infos(t_file *f, struct fat_arch *c, uint32_t n, bool swap)
{
	t_print_infos	*curr;

	if (!n)
		return (NULL);
	curr = get_fat_macho(f, c, swap);
	curr->next = get_fat_infos(f, c + 1, n - 1, swap);
	return (curr);
}

t_print_infos			    *get_fat_infos_32(t_file *f, uint32_t n, bool swap)
{
	struct fat_header	*header;
	struct fat_arch		*arch;
	struct fat_arch		*host;

	header = (struct fat_header *)f->ptr;
	arch = (struct fat_arch *)(header + 1);
	if (!CHECKED((arch + n), f->end))
		return (NULL);
	if ((host = get_host_arch(f->ptr, arch, n, f->end, swap)))
        return (get_fat_macho(f, host, swap));
	return (get_fat_infos(f, arch, n, swap)); //recursive is not necessary a good idea here
}