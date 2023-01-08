# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvincile <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 13:50:43 by tvincile          #+#    #+#              #
#    Updated: 2022/10/17 17:40:52 by tvincile         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c sig.c\
	
NAME = makefile

CC = gcc -g

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

INCLUDES	= -L./library/libft -lft

all : ${NAME}

$(NAME): ${OBJS} library
	${CC} ${CFLAGS} ${INCLUDES} ${OBJS} ${FRAMEWORKS} -o ${NAME}

library: libft libprintf mlx

libft:
	make -s -C library/libft

clean:
	rm -f ${OBJS}
	make -s -C library/libft clean

fclean: clean
	rm -f ${NAME}
	make -s -C library/libft fclean

re : fclean all

.PHONY: all clean fclean re
