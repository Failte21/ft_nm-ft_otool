# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/17 11:11:59 by lsimon            #+#    #+#              #
#    Updated: 2018/12/05 09:40:20 by lsimon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Werror -Wall -Wextra -g

SRCS_DIR = srcs
INC_DIR = inc
OBJS_DIR = objs

NM_NAME = ft_nm
OTOOL_NAME = ft_otool

COMMONS_DIR = commons
NM_DIR = ft_nm
OTOOL_DIR = ft_otool

NM_SRC_NAMES = ft_nm.c
NM_SRC_NAMES += init.c
NM_SRC_NAMES += print.c
NM_SRC_NAMES += x_64.c
NM_SRC_NAMES += x_32.c
NM_SRC_NAMES += tree.c
NM_SRC_NAMES += get_type_c.c
NM_SRC_NAMES += free.c
NM_SRC_NAMES += mh_infos.c

OTOOL_SRC_NAMES = ft_otool.c
OTOOL_SRC_NAMES += init.c
OTOOL_SRC_NAMES += print.c
OTOOL_SRC_NAMES += x_64.c
OTOOL_SRC_NAMES += x_32.c
OTOOL_SRC_NAMES += free.c
OTOOL_SRC_NAMES += mh_infos.c
OTOOL_SRC_NAMES += print_header.c
OTOOL_SRC_NAMES += print_64.c
OTOOL_SRC_NAMES += print_32.c

COMMONS_SRC_NAMES += get_infos.c
COMMONS_SRC_NAMES += errors.c
COMMONS_SRC_NAMES += get_ptr.c
COMMONS_SRC_NAMES += swap.c
COMMONS_SRC_NAMES += swap_32.c
COMMONS_SRC_NAMES += swap_64.c
COMMONS_SRC_NAMES += swap_common.c
COMMONS_SRC_NAMES += get_archname.c
COMMONS_SRC_NAMES += fat_32.c
COMMONS_SRC_NAMES += fat_64.c
COMMONS_SRC_NAMES += init.c

NM_SRCS = $(addprefix $(SRCS_DIR)/$(NM_DIR)/, $(NM_SRC_NAMES))
OTOOL_SRCS = $(addprefix $(SRCS_DIR)/$(OTOOL_DIR)/, $(OTOOL_SRC_NAMES))
COMMON_SRCS = $(addprefix $(SRCS_DIR)/$(COMMONS_DIR), $(COMMONS_SRC_NAMES))

NM_OBJ_NAMES = $(NM_SRC_NAMES:.c=.o)
OTOOL_OBJ_NAMES = $(OTOOL_SRC_NAMES:.c=.o)
COMMON_OBJ_NAMES = $(COMMONS_SRC_NAMES:.c=.o)

NM_OBJS_DIR = $(OBJS_DIR)/$(NM_DIR)
OTOOL_OBJS_DIR = $(OBJS_DIR)/$(OTOOL_DIR)
COMMON_OBJS_DIR = $(OBJS_DIR)/$(COMMONS_DIR)

NM_OBJS = $(addprefix $(NM_OBJS_DIR)/, $(NM_OBJ_NAMES))
OTOOL_OBJS = $(addprefix $(OTOOL_OBJS_DIR)/, $(OTOOL_OBJ_NAMES))
COMMON_OBJS = $(addprefix $(COMMON_OBJS_DIR)/, $(COMMON_OBJ_NAMES))

all: $(NM_NAME) $(OTOOL_NAME)

libft/libft.a:
	@make -C libft/

$(NM_NAME): $(NM_OBJS) $(COMMON_OBJS) libft/libft.a
	$(CC) -o $@ $^

$(OTOOL_NAME): $(OTOOL_OBJS) $(COMMON_OBJS) libft/libft.a
	$(CC) -o $@ $^

$(NM_OBJS_DIR)/%.o: $(SRCS_DIR)/$(NM_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

$(OTOOL_OBJS_DIR)/%.o: $(SRCS_DIR)/$(OTOOL_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

$(COMMON_OBJS_DIR)/%.o: $(SRCS_DIR)/$(COMMONS_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(NM_OBJS)
	rm -f $(OTOOL_OBJS)
	rm -f $(COMMON_OBJS)

fclean: clean
	rm -f $(NM_NAME)
	rm -f $(OTOOL_NAME)

re: fclean all