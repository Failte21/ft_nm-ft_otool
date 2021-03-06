/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:59:58 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/07 14:12:56 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

# include "commons.h"

typedef struct			s_hex_dump {
	char				*datas;
	void				*addr;
	struct section		*sec32;
	struct section_64	*sec64;
}						t_hex_dump;

# define BAD_INDEX_STR "bad string index"

t_print_infos			*init_pinfos(t_hex_dump *hp, bool is_64,\
									bool swap, void *ptr);
int						print_file(t_file *f, char *name);
void					print_header(enum e_ftype type, char *name,\
									t_print_infos *curr);
void					print_dump_64_block(t_hex_dump *hp, bool swap);
void					print_dump_32_block(t_hex_dump *hp, bool swap);
void					print_dump_64_space(t_hex_dump *hp);
void					print_dump_32_space(t_hex_dump *hp);
t_print_infos			*mh_infos(void *ptr, void *end);
struct symtab_command	*get_sc_64(void *ptr, void *end, bool swap);
t_print_infos			*mh_infos_64(void *ptr, bool swap, void *end);
t_hex_dump				*get_hex_dump_64(void *ptr, void *end, bool swap);
struct symtab_command	*get_sc_32(void *ptr, void *end, bool swap);
t_print_infos			*mh_infos_32(void *ptr, bool swap, void *end);
t_hex_dump				*get_hex_dump_32(void *ptr, void *end, bool swap);
int						free_file(t_file *f);

#endif
