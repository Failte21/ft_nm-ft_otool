/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 10:14:11 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/08 10:15:25 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/commons.h"

static t_print_infos	*get_lib_infos_lst(t_file *f, struct ar_hdr *curr)
{
	char			*name;
	char			*p;
	t_print_infos	*el;
	uint32_t		size;

	name = (char *)(curr + 1);
	p = name + ft_strlen(name);
	if (!CHECKED(p, f->end))
		return (handle_error_null("Truncated file\n"));
	while (!(*p))
		p++;
	size = ft_atoi(curr->ar_size);
	if (!(el = mh_infos(p, f->end)))
		return (NULL);
	el->name = name;
	curr = (struct ar_hdr *)(name + size);
	if ((void *)curr > f->end)
		return (handle_error_null("Truncated file\n"));
	if ((void *)curr == f->end)
		return (el);
	el->next = get_lib_infos_lst(f, curr);
	return (el);
}

t_print_infos			*get_lib_infos(t_file *f)
{
	struct ar_hdr	*h;
	struct ar_hdr	*el;

	h = (struct ar_hdr *)(f->ptr + SARMAG);
	el = (struct ar_hdr *)((void *)(h + 1) + ft_atoi(h->ar_size));
	return (get_lib_infos_lst(f, el));
}
