/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 09:27:27 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/22 10:27:19 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

static t_print_infos        *get_fat_macho(void *ptr, struct fat_arch_64 *c, void *end, bool swap)
{
	t_print_infos	*curr;

	if (swap)
		sw_arch_64(c);
	curr = mh_infos(ptr + c->offset, end);
	curr->cputype = c->cputype;
	curr->cpusubtype = c->cpusubtype;
	return (curr);
}

static struct fat_arch_64   *get_host_arch(void *ptr, struct fat_arch_64 *c, uint32_t n, void *end, bool swap)
{
	cpu_type_t  cpu_type;

	if (!n)
		return (NULL);
	cpu_type = swap ? swap_int64(c->cputype) : c->cputype;
    if (cpu_type != CPU_TYPE_X86_64)
        return (get_host_arch(ptr, c + 1, n - 1, end, swap));
    return (c);
}

static t_print_infos	    *get_fat_infos(void *ptr, struct fat_arch_64 *c, uint32_t n, void *end, bool swap)
{
	t_print_infos	*curr;

	if (!n)
		return (NULL);
	curr = get_fat_macho(ptr, c, end, swap);
	curr->next = get_fat_infos(ptr, c + 1, n - 1, end, swap);
	return (curr);
}

t_print_infos			    *get_fat_infos_64(void *ptr, void *end, uint32_t n, bool swap)
{
	struct fat_header	*header;
	struct fat_arch_64		*arch;
	struct fat_arch_64		*host;

	header = (struct fat_header *)ptr;
	arch = (struct fat_arch_64 *)(header + 1);
	if (!CHECKED((arch + n), end))
		return (NULL);
	if ((host = get_host_arch(ptr, arch, n, end, swap)))
        return (get_fat_macho(ptr, host, end, swap));
	return (get_fat_infos(ptr, arch, n, end, swap)); //recursive is not necessary a good idea here
}