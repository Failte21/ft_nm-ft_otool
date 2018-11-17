/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 11:38:06 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/17 13:43:03 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commons.h"

void	*get_ptr(t_macho_file *mf, void *curr, uint32_t offset, size_t s_size)
{
	void	*target;

	target = curr + offset;
	if (target + s_size > mf->end)
	{
		ft_putstr_fd("An error occured\n", 1);
		exit(1);
	}
	return (target);
}