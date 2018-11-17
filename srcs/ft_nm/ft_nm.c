/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:50:04 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/17 13:59:18 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

struct symtab_command	*get_symtab(struct load_command *lc, uint32_t ncmds)
{
	if (ncmds == 0)
		return NULL;
	if (lc->cmd == LC_SYMTAB)
		return ((struct symtab_command *)lc);
	return get_symtab((void *)lc + lc->cmdsize, ncmds - 1);
}

static struct symtab_command	*get_sc(t_macho_file *macho_file)
{
	if (macho_file->is_64)
		return (get_sc_64(macho_file));
	//Todo: handle 32
	return (NULL);
}

static t_sym					*get_symbols(struct symtab_command *sc, t_macho_file *mf)
{
	char			*stringable;

	stringable = mf->ptr + sc->stroff;
	if (mf->is_64)
		return (get_symbols_64(stringable, sc->nsyms, sc->symoff, mf));
	//Todo: handle 32
	return (NULL);
}

int								main(int argc, char **argv)
{
	struct symtab_command	*sc;
	t_sym					*head;
	t_macho_file			*macho_file;

	if (!(macho_file = init_macho_file(argc, argv)))
		return (1);
	if (!(sc = get_sc(macho_file)))
		return (1);
	if (!(head = get_symbols(sc, macho_file)))
		return (1);
	print_tree(head);
	return (0);
}
