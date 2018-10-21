/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:59:58 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/21 09:38:02 by lsimon           ###   ########.fr       */
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

# include "./libft/libft.h"

typedef struct	s_sym {
	unsigned char	type;
	unsigned char	sect;
	unsigned char	sect_index;
	char			*name;
	unsigned long	value;
	struct s_sym	*left;
	struct s_sym	*right;
	char			segname[16];
	char			sectname[16];
}				t_sym;

typedef struct	s_macho_file {
	void		*ptr;
	uint32_t	ncmds;
	bool		is_64;
	bool		is_swap;
	bool		is_fat;
}				t_macho_file;

//Init
t_macho_file			init_macho_file(void *ptr);
t_sym					*init_sym(struct nlist_64 curr, char *stringable, char segname[16], char sectname[16]);


//Print
void 					print_tree(t_sym *curr);

//Errors
int						handle_error(char *msg);
void					*handle_error_null(char *msg);

//x_64
struct symtab_command	*get_sc_64(void *ptr, uint32_t ncmds);
t_sym					*get_symbols_64(char *stringable, uint32_t nsyms, uint32_t symoff, void *ptr);

//Tree
t_sym					*push_back_tree(t_sym *curr, t_sym *to_insert);

//Other
char					get_type_c(char sectname[16], unsigned char type);

#endif