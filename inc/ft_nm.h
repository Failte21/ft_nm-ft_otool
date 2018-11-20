/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:59:58 by lsimon            #+#    #+#             */
/*   Updated: 2018/11/19 17:43:58 by lsimon           ###   ########.fr       */
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

typedef struct 	print_infos {
	t_sym				*sym;
	char				*mh_name;
	struct print_infos	*next;
}				t_print_infos;

typedef struct	s_file {
	void			*ptr;
	void			*end;
	t_print_infos	*head;
	enum ftype		type;
}				t_file;

//Init
t_macho_file				*init_macho_file(int ac, char **av);
t_sym						*init_sym(struct nlist_64 *curr, char *stringable, char segname[16], char sectname[16]);


//Print
void 						print_tree(t_sym *curr);

//Infos
t_print_infos	        	*get_infos_list(t_file *f);
t_file						*get_infos(char *name);
t_print_infos           	*mh_infos(void *ptr, void *end);

//x_64
// t_sym					*get_symbols_64(char *stringable, uint32_t nsyms, uint32_t symoff, t_macho_file *mf);
struct symtab_command		*get_sc_64(void *ptr, void *end, bool swap);
t_print_infos				*mh_infos_64(void *ptr, bool swap, void *end);
t_print_infos				*get_fat_infos_64(void *ptr, void *end, uint32_t n, bool swap);

//x_32
struct symtab_command		*get_sc_32(void *ptr, void *end, bool swap);
t_print_infos				*get_fat_infos_32(void *ptr, void *end, uint32_t n, bool swap);
t_print_infos				*mh_infos_32(void *ptr, bool swap, void *end);

//Tree
t_sym						*push_back_tree(t_sym *curr, t_sym *to_insert);

//Other
char						get_type_c(char sectname[16], unsigned char type);

#endif