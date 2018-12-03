/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:59:58 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/03 08:30:00 by lsimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "commons.h"

typedef struct	s_hex_dump {
	char		*name;
}				t_hex_dump;

typedef struct 	print_infos {
	char				*name;
	struct print_infos	*next;
	cpu_type_t			cputype;
	cpu_subtype_t		cpusubtype;
	bool				is_64;
	bool				failed;
	t_hex_dump			*hex_dump;
}				t_print_infos;

typedef struct	s_file {
	void			*ptr;
	void			*end;
	t_print_infos	*head;
	enum ftype		type;
}				t_file;

#define BAD_INDEX_STR "bad string index"

//Init
t_file						*init_file(char *name);

//Print
int							print_file(t_file *f, char *name, bool multiple);

//Infos
t_print_infos	        	*get_infos_list(t_file *f);
t_file						*get_infos(char *name);
t_print_infos           	*mh_infos(void *ptr, void *end);

//x_64
struct symtab_command		*get_sc_64(void *ptr, void *end, bool swap);
t_print_infos				*get_fat_infos_64(t_file *f, uint32_t n, bool swap);
t_print_infos				*mh_infos_64(void *ptr, bool swap, void *end);
t_hex_dump					*get_hex_dump_64(void *ptr, void *end);

//x_32
struct symtab_command		*get_sc_32(void *ptr, void *end, bool swap);
t_print_infos				*get_fat_infos_32(t_file *f, uint32_t n, bool swap);
t_print_infos				*mh_infos_32(void *ptr, bool swap, void *end);

//free
int							free_file(t_file *f);


#endif