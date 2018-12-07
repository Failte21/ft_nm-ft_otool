/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:38:36 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/07 10:59:44 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

static cpu_type_t	get_cpu64(void *ptr)
{
	struct mach_header_64	*header;

	header = (struct mach_header_64 *)ptr;
	return (header->cputype);
}

static cpu_type_t	get_cpu32(void *ptr)
{
	struct mach_header	*header;

	header = (struct mach_header *)ptr;
	return (header->cputype);
}

t_print_infos		*init_pinfos(t_hex_dump *hp,\
					bool is_64, bool swap, void *ptr)
{
	t_print_infos	*pinfos;

	if (!(pinfos = (t_print_infos *)malloc(sizeof(t_print_infos))))
		return (handle_error_null("Malloc error\n"));
	pinfos->failed = hp == NULL;
	pinfos->next = NULL;
	if (pinfos->failed)
		return (pinfos);
	pinfos->is_64 = is_64;
	pinfos->hex_dump = hp;
	pinfos->swap = swap;
	pinfos->cputype = is_64 ? get_cpu64(ptr) : get_cpu32(ptr);
	return (pinfos);
}
