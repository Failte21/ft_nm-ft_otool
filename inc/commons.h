/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 10:55:18 by lsimon            #+#    #+#             */
/*   Updated: 2018/12/08 10:14:48 by lsimon           ###   ########.fr       */
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
# include <ar.h>

# include "../libft/libft.h"

enum			e_ftype {
	MH,
	FAT,
	LIB,
	UNDEFINED
};

typedef struct	s_arch_info {
	char			*name;
	cpu_type_t		cpu_type;
	cpu_subtype_t	cpu_subtype;
}				t_arch_info;

typedef struct	s_print_infos {
	struct s_sym		*sym;
	char				*name;
	struct s_print_infos	*next;
	cpu_type_t			cputype;
	cpu_subtype_t		cpusubtype;
	bool				is_64;
	bool				failed;
	bool				swap;
	struct s_hex_dump	*hex_dump;
}				t_print_infos;

typedef struct	s_file {
	void			*ptr;
	void			*end;
	t_print_infos	*head;
	enum e_ftype	type;
}				t_file;

t_file			*init_file(char *name);
char			*get_archname(cpu_type_t cputype, cpu_subtype_t cpusubtype);
int				handle_error(char *msg);
void			*handle_error_null(char *msg);
void			*handle_error_free(void *ptr);
t_print_infos	*get_infos_list(t_file *f);
t_file			*get_infos(char *name);
t_print_infos	*get_fat_infos_64(t_file *f, uint32_t n, bool swap);
t_print_infos	*get_fat_infos_32(t_file *f, uint32_t n, bool swap);
t_print_infos	*mh_infos(void *ptr, void *end);
t_print_infos	*get_lib_infos(t_file *f);
uint64_t		swap_int64(uint64_t x);
uint32_t		swap_int32(uint32_t x);
void			sw_mach_header_32(struct mach_header *h);
void			sw_mach_header_64(struct mach_header_64 *h);
void			sw_segment_command_32(struct segment_command *sc);
void			sw_segment_command_64(struct segment_command_64 *sc);
void			sw_section_32(struct section *section);
void			sw_section_64(struct section_64 *section);
void			sw_nlist_64(struct nlist_64 *nl, uint32_t nsyms);
void			sw_nlist_32(struct nlist *nl, uint32_t nsyms);
void			sw_arch_32(struct fat_arch *arch);
void			sw_arch_64(struct fat_arch_64 *arch);
void			sw_symtab_command(struct symtab_command *sc);
void			sw_load_command(struct load_command *lc);

# define CHECKED(s,e) ((void *)(s + 1) < (void *)e)
# define S_32(e,s) (s ? swap_int32(e) : e)

#endif
