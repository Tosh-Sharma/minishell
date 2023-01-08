# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvincile <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 13:50:43 by tvincile          #+#    #+#              #
#    Updated: 2022/05/25 12:29:56 by tvincile         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_atoi.c \
	pushswap_atoi.c \
	ft_itoa.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_isprint.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_strlen.c \
	ft_strlcpy.c \
	ft_strlcat.c \

SRCS_BONUS = ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c \

BONUS_OBJS = ${SRCS_BONUS:.c=.o}

CC = gcc

OBJS = ${SRCS:.c=.o}

NAME = libft.a

CFLAGS =	-Wall -Wextra -Werror

all :		${NAME}

$(NAME):		${OBJS}
	ar rcs ${NAME} ${OBJS}

clean:
	rm -f ${OBJS} ${BONUS_OBJS}

fclean: 	clean
	rm -f ${NAME}

re:				fclean all

bonus:			${BONUS_OBJS} ${NAME}
	ar rcs ${NAME} ${BONUS_OBJS}

%.o: %.c
	gcc ${CFLAGS} -o ${@} -c ${@:.o=.c}

.PHONY: all clean fclean re

