/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:50:04 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/03 08:12:38 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_otool.h"

static int	otool(int ac, char **av)
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
			ft_putstr_fd("An error occured\n", 2); //Malloc error
			errors++;
		}
		else
		{
			errors += print_file(curr, av[i], ac > 2);
			free_file(curr);
		}
		i++;
	}
	return (errors == 0 ? 0 : 1);
}

int		main(int argc, char **argv)
{
	return (otool(argc, argv));
}
