/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 11:38:06 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/17 13:07:13 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commons.h"

void	*get_ptr(t_macho_file *mf, void *curr, uint32_t offset, size_t s_size)
{
	void	*target;

	target = curr + offset;
	if (target + s_size > mf->end)
		exit(1);
	return (target);
}