NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIB = libft.a
SRCS = 	main.c \
		parsing.c \
		signal_handling.c \
		utils/parsing_utils.c \
		utils/basic_utils.c \
		env/env.c env/env_bis.c\
		env/unset.c \
		env/unset_utilities.c \
		expander/expander.c \
		expander/extra_utils.c expander/extra_utils_bis.c \
		executor/executor.c \
		echo/mini_commands.c echo/mini_commannds_utils.c\
		executor/utils.c executor/utils_bis.c

OBJS = ${SRCS:.c=.o}

.c.o:
	$(CC) $(CFLAGS) -c $< -Ilibft

all: ${NAME}

${NAME}: ${OBJS}
	make -C ./libft
	mv libft/${LIB} .
	${CC} ${CFLAGS} $(OBJS) $(LIB) -lreadline ./vendor/readline/lib/libreadline.a -lcurses -o $(NAME)

%.o: %.c
	${CC} ${CFLAGS} -o ${@} -c ${@:.o=.c}

re: fclean all

fclean: clean
	rm -f ${NAME}

clean:
	rm -f ${OBJS} $(LIB) file*

.PHONY: clean fclean re all