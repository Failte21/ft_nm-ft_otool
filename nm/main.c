/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:50:04 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/17 13:52:03 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <mach-o/loader.h>
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

void print_segname(struct segment_command_64 *segment, uint32_t ncmds)
{
	if (ncmds == 0)
		return;
	write(0, segment->segname, 16);
	write(0, "\n", 1);
	print_segname(segment + 1, ncmds - 1);
}

void		dump_segments_command(void *ptr, char is_64, char is_swap, uint32_t ncmds)
{
	struct load_command *cmd;
	cmd = (struct load_command *)((struct mach_header_64 *)ptr + 1);

	if (!is_64)
	{
		//TODO: handle 32
	}
	if (is_swap)
	{
		//TODO: handle swap
	}
	if (cmd->cmd == LC_SEGMENT_64)
	{
		print_segname((struct segment_command_64 *)((struct mach_header_64 *)ptr + 1), ncmds);
	}
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
