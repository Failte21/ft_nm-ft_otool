/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 11:38:06 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/19 14:25:57 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

void	*get_ptr(void *end, void *curr, uint32_t offset, size_t s_size)
{
	void	*target;

	target = curr + offset;
	if (target + s_size > end)
	{
		ft_putstr_fd("An error occured\n", 1);
		return(NULL);
	}
	return (target);
}