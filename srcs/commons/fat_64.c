/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 09:27:27 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/07 14:25:35 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

static t_print_infos		*get_fat_macho(t_file *f,\
					struct fat_arch_64 *c, bool swap)
{
	t_print_infos	*curr;

	if (swap)
		sw_arch_64(c);
	curr = mh_infos(f->ptr + c->offset, f->end);
	curr->cputype = c->cputype;
	curr->cpusubtype = c->cpusubtype;
	return (curr);
}

static struct fat_arch_64	*get_host_arch(struct fat_arch_64 *c,\
										uint32_t n, bool swap)
{
	cpu_type_t	cpu_type;

	if (!n)
		return (NULL);
	cpu_type = swap ? swap_int64(c->cputype) : c->cputype;
	if (cpu_type != CPU_TYPE_X86_64)
		return (get_host_arch(c + 1, n - 1, swap));
	return (c);
}

static t_print_infos		*get_fat_infos(t_file *f,\
					struct fat_arch_64 *c, uint32_t n, bool swap)
{
	t_print_infos	*curr;

	if (!n)
		return (NULL);
	curr = get_fat_macho(f, c, swap);
	curr->next = get_fat_infos(f, c + 1, n - 1, swap);
	return (curr);
}

t_print_infos				*get_fat_infos_64(t_file *f, uint32_t n, bool swap)
{
	struct fat_header		*header;
	struct fat_arch_64		*arch;
	struct fat_arch_64		*host;

	header = (struct fat_header *)f->ptr;
	arch = (struct fat_arch_64 *)(header + 1);
	if (!CHECKED((arch + n), f->end))
		return (handle_error_null("Truncated file\n"));
	if ((host = get_host_arch(arch, n, swap)))
		return (get_fat_macho(f, host, swap));
	return (get_fat_infos(f, arch, n, swap));
}
