/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 10:55:18 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/17 13:04:49 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMONS_H
# define COMMONS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/swap.h>
# include <mach-o/fat.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/mman.h>
# include <unistd.h>
# include <errno.h>

# include "../libft/libft.h"

typedef struct	s_macho_file {
	void		*ptr;
	void		*end;
	uint32_t	ncmds;
	bool		is_64;
	bool		is_swap;
	bool		is_fat;
}				t_macho_file;

//Init
t_macho_file	*init_macho_file(int ac, char **av);

//Errors
int				handle_error(char *msg);
void			*handle_error_null(char *msg);

//Security
void			*get_ptr(t_macho_file *mf, void *curr, uint32_t offset, size_t s_size);

#endif