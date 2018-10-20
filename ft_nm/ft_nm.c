/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:50:04 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/20 12:44:00 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int handle_error(char *msg)
{
	printf("%s : %s\n", msg, strerror(errno));
	return (1);
}

uint32_t	dump_mach_header(void *ptr, char is_64, char is_swap)
{
	struct mach_header_64	*header;
	uint32_t				ncmds;

	if (is_swap)
	{
		//TODO: handle swap stuff
	}
	if (is_64)
	{
		header = (struct mach_header_64 *)ptr;
		ncmds = header->ncmds;
		return (ncmds);
	} 
	else
	{
		//TODO: handle 32
	}
	return (0);
}

void					print_sym(struct symtab_command *symtab, void *ptr)
{
	struct nlist_64	*arr;
	char			*stringable;
	uint32_t		i;

	stringable = ptr + symtab->stroff;
	arr = ptr + symtab->symoff;
	i = 0;
	while (i < symtab->nsyms)
	{
		printf("0000000%llx %s\n",
			arr[i].n_value,
			stringable + arr[i].n_un.n_strx
		);
		i++;
	}
}

struct symtab_command	*get_symtab(struct load_command *lc, uint32_t ncmds)
{
	if (ncmds == 0)
		return NULL;
	if (lc->cmd == LC_SYMTAB)
		return ((struct symtab_command *)lc);
	return get_symtab((void *)lc + lc->cmdsize, ncmds - 1);
}

void					dump_segments_command(void *ptr, char is_64, char is_swap, uint32_t ncmds)
{
	struct load_command		*lc;
	struct symtab_command	*symtab;

	lc = (struct load_command *)((struct mach_header_64 *)ptr + 1);
	if (!is_64)
	{
		//TODO: handle 32
	}
	if (is_swap)
	{
		//TODO: handle swap
	}
	symtab = get_symtab(lc, ncmds);
	print_sym(symtab, ptr);
}

void 		dump_segments(void *ptr)
{
	uint32_t	magic;
	char		is_magic_64;
	char		should_swap;
	char		is_fat;
	uint32_t	ncmds;

	//Get the magic nb and files informations (endian, arch, fat...)
	//Todo: Check for corrupted files
	magic = *(uint32_t *)ptr;
	is_magic_64 = magic == MH_MAGIC_64 || magic == MH_CIGAM_64;
	should_swap = magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM;
	is_fat = magic == FAT_MAGIC || magic == FAT_CIGAM;

	if (is_fat)
	{
		//TODO:handle fat
	}
	else
	{
		ncmds = dump_mach_header(ptr, is_magic_64, should_swap);
		dump_segments_command(ptr, is_magic_64, should_swap,ncmds);
	}
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
	// printf("symbtable is located at %u\n", sc->symoff);
	// print_sym(sc, ptr);
	head = get_symbols(sc, macho_file);
	print_tree(head);
}
