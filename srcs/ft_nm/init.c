/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:38:36 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/06 14:24:57 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

t_print_infos	*init_pinfos(t_sym *sym, bool is_64)
{
	t_print_infos	*pinfos;

	if (!(pinfos = (t_print_infos *)malloc(sizeof(t_print_infos))))
		return (handle_error_null("Malloc error\n"));
	pinfos->failed = sym == NULL;
	pinfos->sym = sym;
	pinfos->next = NULL;
	pinfos->is_64 = is_64;
	return (pinfos);
}