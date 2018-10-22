/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 13:12:41 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/22 10:15:41 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

t_sym					*push_back_tree(t_sym *curr, t_sym *to_insert)
{
	if (!curr)
		return (to_insert);
	if (strcmp(curr->name, to_insert->name) > 0)
		curr->right = push_back_tree(curr->right, to_insert);
	else
		curr->left = push_back_tree(curr->left, to_insert);
	return (curr);
}