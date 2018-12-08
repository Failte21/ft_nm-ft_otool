/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:38:36 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/08 10:13:02 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commons.h"

static enum e_ftype	get_ftype(void *ptr)
{
	uint32_t	magic;

	magic = *(uint32_t *)ptr;
	if (magic == FAT_MAGIC_64 || magic == FAT_MAGIC ||\
		magic == FAT_CIGAM || magic == FAT_CIGAM_64)
		return (FAT);
	if (magic == MH_MAGIC || magic == MH_MAGIC_64 ||\
		magic == MH_CIGAM || magic == MH_CIGAM_64)
		return (MH);
	if (!ft_strncmp((char *)ptr, ARMAG, SARMAG))
		return (LIB);
	return (0);
}

t_file				*init_file(char *name)
{
	t_file		*f;
	int			fd;
	struct stat	buf;

	if (!(f = (t_file *)malloc(sizeof(t_file))))
		return (handle_error_null("Malloc error\n"));
	if ((fd = open(name, O_RDONLY)) < 0)
		return (handle_error_null("Could not open file\n"));
	if (fstat(fd, &buf) < 0)
		return (handle_error_null("Could not retrieve stats on file\n"));
	if ((f->ptr = mmap(0, buf.st_size, PROT_READ |\
		PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (handle_error_null("Failed to map file into virtual memory\n"));
	f->end = f->ptr + buf.st_size;
	if ((close(fd)) < 0)
		return (handle_error_null("An error occured while closing the file\n"));
	if ((f->type = get_ftype(f->ptr)) == UNDEFINED)
		return (handle_error_null("Unknown file type\n"));
	if (!(f->head = get_infos_list(f)))
		return (handle_error_free(f));
	return (f);
}
