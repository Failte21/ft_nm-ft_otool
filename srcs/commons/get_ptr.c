/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 11:38:06 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/22 12:41:19 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commons.h"

void	*get_ptr(t_macho_file *mf, void *curr, uint32_t offset, size_t s_size)
{
	uint32_t	total;
	
	total = curr - mf->ptr;
	total += offset;
	total += s_size;
	if (total > mf->len)
	{
		ft_putstr_fd("An error occured", 1);
		exit(1);
	}
	return (curr + offset);
}