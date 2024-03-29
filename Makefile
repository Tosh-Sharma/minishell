NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIB = libft.a
SRCS = 	main.c \
		parsing.c \
		signal_handling.c \
		utils/basic_utils.c utils/ft_atoi_long_long.c utils/dump_space.c \
		env/env.c env/env_bis.c env/env_utils.c \
		env/unset.c \
		env/unset_utilities.c \
		expander/expander.c expander/extra_utils.c expander/extra_utils_bis.c \
		executor/executor.c executor/process.c \
		executor/single_command_execution.c \
		executor/utils.c executor/utils_bis.c \
		echo/mini_commands.c echo/mini_commands_utils.c echo/mini_pwd_utils.c \
		redirection/io_redirection.c redirection/input_redirection.c \
		redirection/io_utils.c \
		redirection/set_io_redirection_flags.c \
		redirection/output_redirection.c \
 
OBJS = ${SRCS:.c=.o}

.c.o:
	$(CC) $(CFLAGS) -c $< -Ilibft

all: ${NAME}

${NAME}: ${OBJS}
	make -C ./libft
	mv libft/${LIB} .
	${CC} ${CFLAGS} $(OBJS) $(LIB) -lreadline -L ./vendor/readline/lib/ -I ./vendor/readline/include/readline -lncurses -o $(NAME)

%.o: %.c
	${CC} ${CFLAGS} -o ${@} -c ${@:.o=.c}

re: fclean all

fclean: clean
	rm -f ${NAME}

clean:
	make -C ./libft clean
	rm -f ${OBJS} $(LIB) file*

.PHONY: clean fclean re all