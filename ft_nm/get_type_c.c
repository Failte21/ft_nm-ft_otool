/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 14:00:11 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/21 09:57:26 by lsimon           ###   ########.fr       */
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

#include "ft_nm.h"

static char	get_base_char(char sectname[16])
{
	if (!ft_strcmp(sectname, SECT_TEXT))
		return ('T');
	if (!ft_strcmp(sectname, SECT_DATA))
		return ('D');
	if (!ft_strcmp(sectname, SECT_BSS))
		return ('B');
	if (!ft_strcmp(sectname, SECT_COMMON))
		return ('C');
	return ('U');
}

static char	check_scope(unsigned char type, char c)
{
	//Check here if the symbol is external => keep uppercase char
	//Or internal => return lowercase char
	return (type & N_EXT ? c : ft_tolower(c));
}

char	get_type_c(char sectname[16], unsigned char type)
{
	char	c;

	c = get_base_char(sectname);
	c = check_scope(type, c);
	//Todo : Objective C stuff that I don't understand yet
	return (c);
}