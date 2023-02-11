NAME = minishell
CC = gcc
# TODO: Need to prevent warnings from occuring during compilation.
# This requires knowledge of Makefile in more detail. Need to study it.
# TODO: Need to update missing flags like -Wall -Wextra -Werror
CFLAGS = -lreadline
LIBFT_SRC_FILES = ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strncmp.c \
		ft_strcmp.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strnstr.c \
		ft_atoi.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_strmapi.c \
		ft_striteri.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putunbr_fd.c \
		ft_putnbr_16.c \
		ft_putnbr_16_caps.c \
		ft_revstr.c \
		ft_straddchar.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c

LIB_SRC = $(addprefix libft/, $(LIBFT_SRC_FILES))
SRCS = 	main.c \
		parsing.c \
		signal_handling.c \
		utils/parsing_utils.c \
		utils/basic_utils.c \
		env/env.c \
		env/unset.c \
		env/unset_utilities.c \
		expander/expander.c \
		expander/extra_utils.c \
		executor/executor.c \
		$(LIB_SRC)

OBJS = ${SRCS:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
	make -C ./libft
	${CC} ${CFLAGS} -o ${@} ${^} libft/libft.a

%.o: %.c
	${CC} ${CFLAGS} -o ${@} -c ${@:.o=.c}

re: fclean all

fclean: clean
	rm -f ${NAME}

clean:
	rm -f ${OBJS} ${BONUS_OBJS}

.PHONY: clean fclean re all