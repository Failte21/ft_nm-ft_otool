# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/17 11:11:59 by lsimon            #+#    #+#              #
#    Updated: 2018/11/17 10:04:06 by lsimon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Werror -Wall -Wextra -g

SRCS_DIR = srcs
INC_DIR = inc
OBJS_DIR = objs

NM_NAME = ft_nm

COMMONS_DIR = commons
NM_DIR = ft_nm

NM_SRC_NAMES = ft_nm.c
NM_SRC_NAMES += init.c
NM_SRC_NAMES += print.c
NM_SRC_NAMES += x_64.c
NM_SRC_NAMES += tree.c
NM_SRC_NAMES += get_type_c.c

COMMONS_SRC_NAMES = init.c
COMMONS_SRC_NAMES += errors.c
COMMONS_SRC_NAMES += get_ptr.c

NM_SRCS = $(addprefix $(SRCS_DIR)/$(NM_DIR)/, $(NM_SRC_NAMES))
COMMON_SRCS = $(addprefix $(SRCS_DIR)/$(COMMONS_DIR), $(COMMONS_SRC_NAMES))

NM_OBJ_NAMES = $(NM_SRC_NAMES:.c=.o)
COMMON_OBJ_NAMES = $(COMMONS_SRC_NAMES:.c=.o)

NM_OBJS_DIR = $(OBJS_DIR)/$(NM_DIR)
COMMON_OBJS_DIR = $(OBJS_DIR)/$(COMMONS_DIR)

NM_OBJS = $(addprefix $(NM_OBJS_DIR)/, $(NM_OBJ_NAMES))
COMMON_OBJS = $(addprefix $(COMMON_OBJS_DIR)/, $(COMMON_OBJ_NAMES))

all: $(NM_NAME)

$(NM_NAME): $(NM_OBJS) $(COMMON_OBJS)
	$(CC) -L srcs/libft -lft -o $@ $^

$(NM_OBJS_DIR)/%.o: $(SRCS_DIR)/$(NM_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

$(COMMON_OBJS_DIR)/%.o: $(SRCS_DIR)/$(COMMONS_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(NM_OBJS)
	rm -f $(COMMON_OBJS)

fclean: clean
	rm -f $(NM_NAME)

re: fclean all