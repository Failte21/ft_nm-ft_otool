/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 14:00:11 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/20 14:06:19 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char	get_base_char(char segname[16])
{
	if (strcmp(segname, SEG_TEXT))
		return ("T");
	if (strcmp(segname, SEG_DATA))
		return ("T");
	if (strcmp(segname, SEG_OBJC))
		return ("T");
	if (strcmp(segname, SEG_TEXT))
		return ("T");
}

char	get_type_c(t_sym *sym)
{
	char	c;

	c = get_base_char(sym->segname);
}