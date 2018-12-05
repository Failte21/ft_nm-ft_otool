/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:59:58 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/05 09:22:38 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "commons.h"

typedef struct	s_hex_dump {
	char				*datas;
	void				*addr;
	struct section		*sec32;
	struct section_64	*sec64;
}				t_hex_dump;

#define BAD_INDEX_STR "bad string index"

//Init
t_print_infos				*init_pinfos(t_hex_dump *hp, bool is_64, bool swap, void *ptr);

//Print
int							print_file(t_file *f, char *name);
void						print_header(enum ftype type, char *name, t_print_infos *curr);

//Infos
t_print_infos           	*mh_infos(void *ptr, void *end);

//x_64
struct symtab_command		*get_sc_64(void *ptr, void *end, bool swap);
t_print_infos				*mh_infos_64(void *ptr, bool swap, void *end);
t_hex_dump					*get_hex_dump_64(void *ptr, void *end, bool swap);

//x_32
struct symtab_command		*get_sc_32(void *ptr, void *end, bool swap);
t_print_infos				*mh_infos_32(void *ptr, bool swap, void *end);
t_hex_dump					*get_hex_dump_32(void *ptr, void *end, bool swap);

//free
int							free_file(t_file *f);

#endif