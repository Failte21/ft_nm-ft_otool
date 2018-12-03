/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:38:36 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/03 16:12:13 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

t_print_infos	*init_pinfos(t_hex_dump *hp, bool is_64, bool swap)
{
	t_print_infos	*pinfos;

	if (!(pinfos = (t_print_infos *)malloc(sizeof(t_print_infos))))
		return (NULL);
	pinfos->failed = false; //TODO: unmock
	pinfos->next = NULL;
	pinfos->is_64 = is_64;
	pinfos->hex_dump = hp;
	pinfos->swap = swap;
	return (pinfos);
}