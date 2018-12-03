/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:38:36 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/03 16:12:04 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

t_print_infos	*init_pinfos(t_sym *sym, bool is_64)
{
	t_print_infos	*pinfos;

	if (!(pinfos = (t_print_infos *)malloc(sizeof(t_print_infos))))
		return (NULL);
	pinfos->failed = sym == NULL;
	pinfos->sym = sym;
	pinfos->next = NULL;
	pinfos->is_64 = is_64;
	return (pinfos);
}