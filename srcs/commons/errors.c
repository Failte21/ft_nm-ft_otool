/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:48:37 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/29 12:23:59 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

//Todo: remove printf
//Todo: print on stderr
int 	handle_error(char *msg)
{
	printf("%s : %s\n", msg, strerror(errno));
	return (1);
}

//Todo: decide if we keep the message
void	*handle_error_null(char *msg)
{
	void	*a = ft_strcmp(msg, "yolo") == 0 ? NULL : NULL;
	return (a);
}

void	*handle_error_free(void *ptr)
{
	free(ptr);
	return (NULL);
}