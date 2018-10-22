/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:59:58 by lsimon            #+#    #+#             */
/*   Updated: 2018/10/22 11:22:21 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "commons.h"

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

//Init
t_macho_file			*init_macho_file(int ac, char **av);
t_sym					*init_sym(struct nlist_64 curr, char *stringable, char segname[16], char sectname[16]);


//Print
void 					print_tree(t_sym *curr);

//x_64
struct symtab_command	*get_sc_64(void *ptr, uint32_t ncmds);
t_sym					*get_symbols_64(char *stringable, uint32_t nsyms, uint32_t symoff, void *ptr);

//Tree
t_sym					*push_back_tree(t_sym *curr, t_sym *to_insert);

//Other
char					get_type_c(char sectname[16], unsigned char type);

#endif