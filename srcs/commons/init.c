/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:38:36 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/17 12:18:07 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commons.h"

static uint32_t	get_ncmds(t_macho_file *mf)
{
	struct mach_header_64	*header;

	if (mf->is_64)
	{
		header = (struct mach_header_64 *)mf->ptr;
		header = (struct mach_header_64 *)get_ptr(mf, mf->ptr, 0, sizeof(struct mach_header_64));
		return (header->ncmds);
	} 
	return (0);
}

t_macho_file	*init_macho_file(int ac, char **av)
{
	uint32_t		magic;
	t_macho_file	*macho_file;
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
	if ((close(fd)) < 0)
		return (handle_error_null("An error occured while clising the fileq\n"));
	if (!(macho_file = (t_macho_file *)malloc(sizeof(macho_file))))
		return (NULL);
	//Get the magic nb and files informations (endian, arch, fat...)
	magic = *(uint32_t *)ptr;
	macho_file->is_64 = magic == MH_MAGIC_64 || magic == MH_CIGAM_64;
	macho_file->is_swap = magic == MH_CIGAM || magic == MH_CIGAM_64 || magic == FAT_CIGAM;
	macho_file->is_fat = magic == FAT_MAGIC || magic == FAT_CIGAM;
	macho_file->ptr = ptr;
	macho_file->len = buf.st_size;

	macho_file->ncmds = get_ncmds(macho_file);
	return macho_file;
}