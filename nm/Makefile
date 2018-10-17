# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsimon <lsimon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/17 11:11:59 by lsimon            #+#    #+#              #
#    Updated: 2018/10/17 13:45:37 by lsimon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Werror -Wall -Wextra -g
OBJS = $(SRCS:.c=.o)
NAME = nm

SRCS = main.c

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all