/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:50:04 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/20 14:37:22 by lsimon           ###   ########.fr       */
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

// static struct symtab_command	*get_sc(t_macho_file *macho_file)
// {
// 	if (macho_file->is_64)
// 		return (get_sc_64(macho_file));
// 	//Todo: handle 32
// 	return (NULL);
// }

// static t_sym					*get_symbols(struct symtab_command *sc, t_macho_file *mf)
// {
// 	char			*stringable;

// 	stringable = mf->ptr + sc->stroff;
// 	if (mf->is_64)
// 		return (get_symbols_64(stringable, sc->nsyms, sc->symoff, mf));
// 	//Todo: handle 32
// 	return (NULL);
// }

void							nm(int ac, char **av)
{
	int				i;
	t_file			*curr;

	i = 1;
	while (i < ac)
	{
		if (!(curr = get_infos(av[i])))
			printf("error"); //Todo: handle print inside ?
		else
			print_file(curr, av[i]);
		//TODO: free infos
		i++;
	}
}

int								main(int argc, char **argv)
{
	// if (argc < 2)
	// 	return (1);
	nm(argc, argv);
	return (0);
}
