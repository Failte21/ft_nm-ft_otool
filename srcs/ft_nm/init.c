/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:38:36 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/19 12:57:05 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

t_sym			*init_sym(struct nlist_64 *curr, char *stringable, char segname[16], char sectname[16])
{
	t_sym	*new_sym;

	if (!(new_sym = (t_sym *)malloc(sizeof(t_sym))))
		return (NULL);
	new_sym->value = curr->n_value;
	new_sym->name = stringable + curr->n_un.n_strx;
	new_sym->type = curr->n_type;
	new_sym->left = NULL;
	new_sym->right = NULL;
	if (segname)
		strcpy(new_sym->segname, segname);
	if (sectname)
		strcpy(new_sym->sectname, sectname);
	return (new_sym);
}

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
	if ((f->ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (handle_error_null("Failed to map file into virtual memory"));
	if ((close(fd)) < 0)
		return (handle_error_null("An error occured while closing the file\n"));
	if ((f->type = get_ftype(f->ptr)) == UNDEFINED)
		return (NULL);
	if (!(f->head = get_infos_list(f)))
		return (NULL);
	return (f);
}

t_file			*get_infos(char *name)
{
	t_file	*f;

	if (!(f = init_file(name)))
		return (NULL);
	return (f);
}