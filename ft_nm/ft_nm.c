/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:50:04 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/20 13:14:47 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

struct symtab_command	*get_symtab(struct load_command *lc, uint32_t ncmds)
{
	if (ncmds == 0)
		return NULL;
	if (lc->cmd == LC_SYMTAB)
		return ((struct symtab_command *)lc);
	return get_symtab((void *)lc + lc->cmdsize, ncmds - 1);
}

struct symtab_command	*get_sc(t_macho_file macho_file)
{
	if (macho_file.is_64)
		return (get_sc_64(macho_file.ptr, macho_file.ncmds));
	//Todo: handle 32
	return (NULL);
}

t_sym					*get_symbols(struct symtab_command *sc, t_macho_file mf)
{
	char			*stringable;

	stringable = mf.ptr + sc->stroff;
	if (mf.is_64)
		return (get_symbols_64(stringable, sc->nsyms, sc->symoff, mf.ptr));
	//Todo: handle 32
	return (NULL);
}

void					*get_ptr(int ac, char **av)
{
	int						fd;
	void					*ptr;
	struct stat				buf;

	if (ac < 2)
		return (handle_error_null("usage: ./ft_nm exfile\n"));
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (handle_error_null("Could not open file\n"));
	if (fstat(fd, &buf) < 0)
		return (handle_error_null("Could not retrieve stats on file"));
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (handle_error_null("Failed to map file into virtual memory"));
	return (ptr);
}

int						main(int argc, char **argv)
{
	void					*ptr;
	struct symtab_command	*sc;
	t_sym					*head;
	t_macho_file			macho_file;

	if (!(ptr = get_ptr(argc, argv)))
		return (1);

	macho_file = init_macho_file(ptr);
	sc = get_sc(macho_file);
	head = get_symbols(sc, macho_file);
	print_tree(head);
}
