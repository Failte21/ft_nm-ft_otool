/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:38:36 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/03 08:13:38 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

enum ftype get_ftype(void *ptr)
{
	uint32_t	magic;

	magic = *(uint32_t *)ptr;
	if (magic == FAT_MAGIC_64 || magic == FAT_MAGIC || magic == FAT_CIGAM || magic == FAT_CIGAM_64)
		return (FAT);
	if (magic == MH_MAGIC || magic == MH_MAGIC_64 || magic == MH_CIGAM || magic == MH_CIGAM_64)
		return (MH);
	return (LIB); //Not sure at all this is enough to check
}

t_print_infos	*init_pinfos(bool is_64)
{
	t_print_infos	*pinfos;

	if (!(pinfos = (t_print_infos *)malloc(sizeof(t_print_infos))))
		return (NULL);
	pinfos->failed = true; //TODO: unmock
	pinfos->next = NULL;
	pinfos->is_64 = is_64;
	return (pinfos);
}

t_file			*init_file(char *name)
{
	t_file		*f;
	int			fd;
	struct stat	buf;

	if (!(f = (t_file *)malloc(sizeof(t_file))))
		return (handle_error_null("Malloc error"));
	if ((fd = open(name, O_RDONLY)) < 0)
		return (handle_error_null("Could not open file\n"));
	if (fstat(fd, &buf) < 0)
		return (handle_error_null("Could not retrieve stats on file"));
	if ((f->ptr = mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (handle_error_null("Failed to map file into virtual memory"));
	f->end = f->ptr + buf.st_size;
	if ((close(fd)) < 0)
		return (handle_error_null("An error occured while closing the file\n"));
	if ((f->type = get_ftype(f->ptr)) == UNDEFINED)
		return (NULL);
	if (!(f->head = get_infos_list(f)))
		return (handle_error_free(f));
	return (f);
}