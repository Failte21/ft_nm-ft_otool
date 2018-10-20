/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:50:04 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/20 12:51:51 by lsimon           ###   ########.fr       */
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

struct symtab_command	*get_sc_64(void *ptr, uint32_t ncmds)
{
	uint32_t					i;
	struct load_command			*lc;

	lc = (struct load_command *)((struct mach_header_64 *)ptr + 1);
	i = 0;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
			return (struct symtab_command *)lc;
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
	return NULL;
}

struct symtab_command	*get_sc(t_macho_file macho_file)
{
	if (macho_file.is_64)
		return (get_sc_64(macho_file.ptr, macho_file.ncmds));
	//Todo: handle 32
	return (NULL);
}

t_sym					*push_back_tree(t_sym *curr, t_sym *to_insert)
{
	if (!curr)
		return (to_insert);
	if (strcmp(curr->name, to_insert->name) > 0)
		curr->right = push_back_tree(curr->right, to_insert);
	else
		curr->left = push_back_tree(curr->left, to_insert);
	return (curr);
}

t_sym					*get_symbols(struct symtab_command *sc, t_macho_file mf)
{
	t_sym			*head;
	t_sym			*to_insert;
	char			*stringable;
	struct nlist_64	*arr;
	uint32_t		i;

	stringable = mf.ptr + sc->stroff;
	head = NULL;
	arr = mf.ptr + sc->symoff;
	i = 0;
	while (i < sc->nsyms)
	{
		to_insert = init_sym(arr[i], stringable);
		head = push_back_tree(head, to_insert);
		i++;
	}
	return (head);
}

int	main(int argc, char **argv)
{
	const char				*filename = argv[1];
	int						fd;
	void					*ptr;
	struct stat				buf;
	struct symtab_command	*sc;
	t_sym					*head;
	t_macho_file			macho_file;

	if (argc < 2)
		return (handle_error("usage: ./ft_nm exfile\n"));

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (handle_error("Could not open file\n"));
	
	if (fstat(fd, &buf) < 0)
		return (handle_error("Could not retrieve stats on file"));

	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (handle_error("Failed to map file into virtual memory"));

	macho_file = init_macho_file(ptr);
	sc = get_sc(macho_file);
	head = get_symbols(sc, macho_file);
	print_tree(head);
}
