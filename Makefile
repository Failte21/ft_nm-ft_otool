# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/17 11:11:59 by lsimon            #+#    #+#              #
#    Updated: 2018/10/22 10:20:07 by lsimon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Werror -Wall -Wextra -g

SRCS_DIR = srcs
INC_DIR = inc
OBJS_DIR = objs

NM_NAME = ft_nm

NM_DIR = ft_nm

NM_SRC_NAMES = ft_nm.c
NM_SRC_NAMES += init.c
NM_SRC_NAMES += print.c
NM_SRC_NAMES += errors.c
NM_SRC_NAMES += x_64.c
NM_SRC_NAMES += tree.c
NM_SRC_NAMES += get_type_c.c

NM_SRCS = $(addprefix $(SRCS_DIR)/$(NM_DIR)/, $(NM_SRC_NAMES))

NM_OBJS = $(NM_SRC_NAMES:.c=.o)

all: $(NM_NAME)

$(NM_NAME): $(NM_OBJS)
	$(CC) -L srcs/libft -lft -o $@ $^

%.o: $(SRCS_DIR)/$(NM_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm $(NM_OBJS)

fclean: clean
	rm $(NM_NAME)

re: fclean all