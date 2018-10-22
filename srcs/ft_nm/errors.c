/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 12:48:37 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/22 10:15:20 by lsimon           ###   ########.fr       */
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

void	*handle_error_null(char *msg)
{
	printf("%s : %s\n", msg, strerror(errno));
	return (NULL);
}