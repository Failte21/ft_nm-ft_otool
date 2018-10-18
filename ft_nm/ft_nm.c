/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:50:04 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/18 12:27:14 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <mach-o/swap.h>
#include <mach-o/fat.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>

/* hack until arm64 headers are worked out */
#ifndef CPU_TYPE_ARM64
# define CPU_TYPE_ARM64			(CPU_TYPE_ARM | CPU_ARCH_ABI64)
#endif /* !CPU_TYPE_ARM64 */

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
		printf("%s\n", stringable + arr[i].n_un.n_strx);
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

int handle_error(char *msg)
{
	printf("%s : %s\n", msg, strerror(errno));
	return (1);
}

int	main(int argc, char **argv)
{
	const char	*filename = argv[1];
	int			fd;
	void		*ptr;
	struct stat	buf;

	if (argc < 2)
		return (handle_error("usage: ./ft_nm exfile\n"));

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (handle_error("Could not open file\n"));
	
	if (fstat(fd, &buf) < 0)
		return (handle_error("Could not retrieve stats on file"));

	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (handle_error("Failed to map file into virtual memory"));

	dump_segments(ptr);
}
