/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_common.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:04:48 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/08 09:29:24 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commons.h"

void	sw_symtab_command(struct symtab_command *sc)
{
	sc->symoff = swap_int32(sc->symoff);
	sc->nsyms = swap_int32(sc->nsyms);
	sc->stroff = swap_int32(sc->stroff);
	sc->strsize = swap_int32(sc->strsize);
}

void	sw_load_command(struct load_command *lc)
{
	lc->cmd = swap_int32(lc->cmd);
	lc->cmdsize = swap_int32(lc->cmdsize);
}
