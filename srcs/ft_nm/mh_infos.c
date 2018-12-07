/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mh_infos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:03:28 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/07 09:14:35 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

t_print_infos		*mh_infos(void *ptr, void *end)
{
	uint32_t				magic;
	struct symtab_command	*sc;
	bool					is_64;
	bool					swap;
	t_sym					*sym;

	if (!CHECKED((uint32_t *)ptr, end))
		return (init_pinfos(NULL, false));
	magic = *(uint32_t *)ptr;
	is_64 = magic == MH_CIGAM_64 || magic == MH_MAGIC_64;
	swap = magic == MH_CIGAM_64 || magic == MH_CIGAM;
	if (!(sc = is_64 ?\
		get_sc_64(ptr, end, swap) :\
		get_sc_32(ptr, end, swap)))
		return (init_pinfos(NULL, is_64));
	if (swap)
		sw_symtab_command(sc);
	sym = is_64 ?\
		get_sym_64(sc, ptr, end, swap) :\
		get_sym_32(sc, ptr, end, swap);
	return (init_pinfos(sym, is_64));
}
