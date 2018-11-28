/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:50:04 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/28 11:17:10 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

static int						nm(int ac, char **av)
{
	int				i;
	t_file			*curr;
	int				errors;

	i = 1;
	errors = 0;
	while (i < ac)
	{
		if (!(curr = get_infos(av[i])))
		{
			ft_putstr_fd("An error occured\n", 2); //Todo: handle print inside ?
			errors++;
		}
		else
		{
			print_file(curr, av[i], ac > 2);
			free_file(curr);
		}
		i++;
	}
	return (errors == 0 ? 0 : 1);
}

int								main(int argc, char **argv)
{
	return (nm(argc, argv));
}
