/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 10:28:56 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/07 10:59:03 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

static void		free_infos(t_print_infos *curr)
{
	if (!curr)
		return ;
	free_infos(curr->next);
	free(curr);
}

int				free_file(t_file *f)
{
	free_infos(f->head);
	if (munmap(f->ptr, (f->end - f->ptr)) == -1)
		return (-1);
	free(f);
	return (0);
}
