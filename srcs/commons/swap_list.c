/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 14:53:08 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/08 13:13:43 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commons.h"

static void	sw_nlist_one_64(struct nlist_64 *nl)
{
	nl->n_un.n_strx = swap_int64(nl->n_un.n_strx);
	nl->n_value = swap_int64(nl->n_value);
}

void		sw_nlist_64(struct nlist_64 *nl, uint32_t nsyms)
{
	uint32_t	i;

	i = 0;
	while (i < nsyms)
	{
		sw_nlist_one_64(nl + i);
		i++;
	}
}

static void	sw_nlist_one_32(struct nlist *nl)
{
	nl->n_un.n_strx = swap_int32(nl->n_un.n_strx);
	nl->n_value = swap_int32(nl->n_value);
}

void		sw_nlist_32(struct nlist *nl, uint32_t nsyms)
{
	uint32_t	i;

	i = 0;
	while (i < nsyms)
	{
		sw_nlist_one_32(nl + i);
		i++;
	}
}
