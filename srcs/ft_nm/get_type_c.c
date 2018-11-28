/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 14:00:11 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/28 10:00:38 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// ---------------- interesting section from man nm -------------------------
// this
// value  is  followed  by one of the following characters, representing the symbol type: U (undefined), A (abso-
// lute), T (text section symbol), D (data section symbol), B (bss section symbol), C  (common  symbol),  -  (for
// debugger  symbol  table entries; see -a below), S (symbol in a section other than those above), or I (indirect
// symbol).  If the symbol is local (non-external), the symbol's type is instead represented by the corresponding
// lowercase  letter.   A  lower  case u in a dynamic shared library indicates a undefined reference to a private
// external in another module in the same library.

// If the symbol is a Objective C method, the symbol name is  +-[Class_name(category_name)	method:name:],	where
// `+'  is for class methods, `-' is for instance methods, and (category_name) is present only when the method is
// in a category.

#include "../../inc/ft_nm.h"

static char check_scope(char c, unsigned char type)
{
	if ((type & N_EXT) && c != '?')
		return (ft_toupper(c));
	return (c);
}

//Todo : also check segname ? 
static char	from_names(char sectname[16], unsigned char type, char segname[16])
{
	if (!ft_strcmp(sectname, SECT_TEXT) && !ft_strcmp(segname, SEG_TEXT))
		return (check_scope('t', type));
	if (!ft_strcmp(sectname, SECT_DATA) && !ft_strcmp(segname, SEG_DATA))
		return (check_scope('d', type));
	if (!ft_strcmp(sectname, SECT_BSS) && !ft_strcmp(segname, SEG_DATA))
		return (check_scope('b', type));
	return(check_scope('s', type));
}

char		get_type_c(t_sym *sym)
{
	char 	m;
	
	if (sym->type & N_STAB)
		return (check_scope('-', sym->type));
	m = sym->type & N_TYPE;
	if (m == N_UNDF)
		return (check_scope(sym->value != 0 ? 'c' : 'u', sym->type));
	if (m == N_PBUD)
		return (check_scope('u', sym->type));
	if (m == N_ABS)
		return (check_scope('a', sym->type));
	if (m == N_SECT && sym->n_sect != NO_SECT && sym->n_sect <= MAX_SECT)
		return (from_names(sym->sectname, sym->type, sym->segname));
	if (m == N_INDR)
		return (check_scope('i', sym->type));
	return (check_scope('?', sym->type));
}