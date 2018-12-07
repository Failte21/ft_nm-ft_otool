/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:59:58 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/07 14:10:11 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "commons.h"

typedef struct				s_sym {
	unsigned char	type;
	unsigned char	sect;
	unsigned char	sect_index;
	unsigned char	n_sect;
	char			*name;
	unsigned long	value;
	struct s_sym	*left;
	struct s_sym	*right;
	char			segname[16];
	char			sectname[16];
}							t_sym;

typedef struct				s_sym_r32 {
	uint32_t		nsyms;
	char			*stringable;
	struct nlist	*arr;
}							t_sym_r;

typedef struct				s_sym_r64 {
	uint32_t		nsyms;
	char			*stringable;
	struct nlist_64	*arr;
}							t_sym_r64;

# define BAD_INDEX_STR "bad string index"

t_print_infos				*init_pinfos(t_sym *sym, bool is_64);
int							print_file(t_file *f, char *name, bool multiple);
void						print_header(enum e_ftype type, bool multiple,\
										char *name, t_print_infos *curr);
t_print_infos				*mh_infos(void *ptr, void *end);
t_sym						*get_sym_64(struct symtab_command *sc,\
										void *ptr, void *end, bool swap);
struct symtab_command		*get_sc_64(void *ptr, void *end, bool swap);
t_print_infos				*mh_infos_64(void *ptr, bool swap, void *end);
t_sym						*get_sym_32(struct symtab_command *sc,\
										void *ptr, void *end, bool swap);
struct symtab_command		*get_sc_32(void *ptr, void *end, bool swap);
t_print_infos				*mh_infos_32(void *ptr, bool swap, void *end);
t_sym						*push_back_tree(t_sym *curr, t_sym *to_insert);
char						get_type_c(t_sym *sym);
int							free_file(t_file *f);
void						free_tree(t_sym *curr);

#endif
