/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_common.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 11:04:48 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/21 11:21:52 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commons.h"

void    sw_symtab_command(struct symtab_command *sc)
{
	sc->cmd = swap_int32(sc->cmd);
	sc->cmdsize = swap_int32(sc->cmdsize);
	sc->symoff = swap_int32(sc->symoff);
	sc->nsyms = swap_int32(sc->nsyms);
	sc->stroff = swap_int32(sc->stroff);
	sc->strsize = swap_int32(sc->strsize);
}
