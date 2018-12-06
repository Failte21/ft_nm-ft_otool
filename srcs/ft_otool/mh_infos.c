/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mh_infos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:03:03 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/06 11:10:53 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

t_print_infos			*mh_infos(void *ptr, void *end)
{
    uint32_t                magic;
    bool                    is_64;
    bool                    swap;
	t_hex_dump				*hex_dump;

	if (!CHECKED((uint32_t *)ptr, end))
		return (init_pinfos(NULL, false, false, ptr));
    magic = *(uint32_t *)ptr;
    is_64 = magic == MH_CIGAM_64 || magic == MH_MAGIC_64;
    swap = magic == MH_CIGAM_64 || magic == MH_CIGAM;
	hex_dump = is_64 ?\
		get_hex_dump_64(ptr, end, swap):\
		get_hex_dump_32(ptr, end, swap);
	return (init_pinfos(hex_dump, is_64, swap, ptr));
}