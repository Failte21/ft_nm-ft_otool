/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 14:00:11 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/07 09:10:24 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

static char	check_scope(char c, unsigned char type)
{
	if (type & N_EXT)
		return (ft_toupper(c));
	return (c);
}

static char	from_names(char sectname[16], unsigned char type, char segname[16])
{
	if (!ft_strcmp(sectname, SECT_TEXT) && !ft_strcmp(segname, SEG_TEXT))
		return (check_scope('t', type));
	if (!ft_strcmp(sectname, SECT_DATA) && !ft_strcmp(segname, SEG_DATA))
		return (check_scope('d', type));
	if (!ft_strcmp(sectname, SECT_BSS) && !ft_strcmp(segname, SEG_DATA))
		return (check_scope('b', type));
	return (check_scope('s', type));
}

char		get_type_c(t_sym *sym)
{
	char	m;

	if (sym->type & N_STAB)
		return ('-');
	m = sym->type & N_TYPE;
	if (m == N_UNDF)
		return (check_scope(sym->value != 0 ? 'c' : 'u', sym->type));
	if (m == N_PBUD)
		return (check_scope('u', sym->type));
	if (m == N_ABS)
		return (check_scope('a', sym->type));
	if (m == N_SECT)
		return (from_names(sym->sectname, sym->type, sym->segname));
	if (m == N_INDR)
		return (check_scope('i', sym->type));
	return ('?');
}
