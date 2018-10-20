/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:59:58 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/20 12:41:00 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

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

// struct nlist {
// 	union {
// 		char *n_name;	/* for use when in-core */
// 		long  n_strx;	/* index into the string table */
// 	} n_un;
// 	unsigned char n_type;	/* type flag, see below */
// 	unsigned char n_sect;	/* section number or NO_SECT */
// 	short	      n_desc;	/* see <mach-o/stab.h> */
// 	unsigned long n_value;	/* value of this symbol (or stab offset) */
// };

typedef struct	s_sym {
	unsigned char	type;
	unsigned char	sect;
	unsigned char	sect_index;
	char			*name;
	unsigned long	value;
	struct s_sym	*left;
	struct s_sym	*right;
}				t_sym;

typedef struct	s_macho_file {
	void		*ptr;
	uint32_t	ncmds;
	bool		is_64;
	bool		is_swap;
	bool		is_fat;
}				t_macho_file;

t_macho_file	init_macho_file(void *ptr);
t_sym			*init_sym(struct nlist_64 curr, char *stringable);

#endif