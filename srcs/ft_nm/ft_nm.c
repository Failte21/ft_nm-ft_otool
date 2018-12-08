/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:50:04 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/08 12:19:29 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_nm.h"

static int						no_args(void)
{
	int				errors;
	t_file			*curr;

	errors = 0;
	if (!(curr = get_infos("a.out")))
	{
		ft_putstr_fd("An error occured\n", 2);
		errors++;
	}
	else
	{
		errors += print_file(curr, "a.out", false);
		free_file(curr);
	}
	return (errors);
}

static int						nm(int ac, char **av)
{
	int				i;
	t_file			*curr;
	int				errors;

	i = 1;
	errors = 0;
	if (ac < 2)
		return (no_args());
	while (i < ac)
	{
		if (!(curr = get_infos(av[i])))
		{
			ft_putstr_fd("An error occured\n", 2);
			errors++;
		}
		else
			errors += print_file(curr, av[i], ac > 2);
		free_file(curr);
		i++;
	}
	return (errors == 0 ? 0 : 1);
}

int								main(int argc, char **argv)
{
	return (nm(argc, argv));
}
