# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/17 11:11:59 by lsimon            #+#    #+#              #
#    Updated: 2018/10/20 13:13:57 by lsimon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Werror -Wall -Wextra -g
OBJS = $(SRCS:.c=.o)
NAME = ft_nm

SRCS = ft_nm.c
SRCS += init.c
SRCS += print.c
SRCS += errors.c
SRCS += x_64.c
SRCS += tree.c

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all