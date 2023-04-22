/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:55:38 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/22 15:00:47 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** Libs
*/
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <termios.h>
# include "libft/libft.h"
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>

# define CYAN "\001\033[1;36m\002"
# define WHITE "\001\033[0m\002"
# define GREEN "\001\033[1;32m\002"

typedef struct s_shell
{
	char	*input;
	char	**envp;
	int		return_value;
	int		env_y;
	char	**env_input;
	char	*res_com;
	int		new_line_flag;
	char	**split_com;
	int		is_heredoc_active;
	int		heredoc_fd;
	int		temp_fd;
}	t_shell;

void	parser(t_shell *shell);
void	rl_replace_line(const char *input, int number);
void	main_signal_handling(void);
void	copy_env_variables(t_shell *shell, char **envp);
void	check_for_incorrect_syntax(char *input);
void	perror_and_exit(char *input, int exit_code);
void	*ft_malloc_checker(int type, int size);
void	execute_commands(t_shell *shell, char **splitted_commands, int count);
void	env_command(t_shell *shell, int flag);
void	export_command(t_shell *shell, char *input);
void	unset_command(t_shell *shell, char *input);
int		join_and_cmp(const char *s1, const char *s2, size_t n);
void	expander(char **commands, t_shell *shell);
char	*replace_env_variable(char *command, int *positions, int count,
			t_shell *shell);
void	mini_echo(char *command, int index, t_shell *shell);
void	mini_pwd(void);
void	mini_cd(t_shell *shell);
void	env_count_update(t_shell *shell);
char	*find_appropriate_path(char **command, char **address);
void	execute_builtin(char *command, t_shell *shell);
int		is_builtin_command(t_shell *shell);
int		get_index(char *command, int i);
void	single_command_execution(t_shell *shell, char **splitted_commands);
void	store_latest_variables(t_shell *shell, char *str);
char	**realloc_new_and_copy_old(t_shell *shell, int count);
char	*get_var(char *command, int nb, char *var, int len);
char	*replace_var(char *new_var, char *var, char *env_row, int return_value);
void	change_pwd(t_shell *shell);
void	pwd_refresh(t_shell *shell);
void	get_back_home(t_shell *shell);
void	exit_one(t_shell *shell);
void	exit_multiple(t_shell *shell, int i);
void	mini_return_value(t_shell *shell);
void	execute_process(t_shell *shell, char *command);
int		ft_isnumber(char *num);
int		equal_checker(char *envp);
void	new_prompt(t_shell *shell);
void	io_redirection(t_shell *shell, int is_piped, int redirect_fd);
int		input_redirection(t_shell *shell);
int		output_redirection(t_shell *shell);
void	append_to_file(char *file_name);
void	write_to_file(char *file_name);
void	heredoc(char *delimiter);
void	read_from_file(char *file_name);
int		get_list_size(char **input);
int		get_new_list_size(char **input, int old_size, char *in_1, char *in_2);
void	create_new_string(t_shell *shell, int new_size, char *in1, char *in2);
void	set_io_redirection_flags(t_shell *shell);
void	free_strings(char **str);
int		is_env_var(char *str, t_shell *shell);
void	add_env_var(char *str, t_shell *shell);
void	update_env_var(char *str, t_shell *shell);
void	command_not_found(char *str, int flag);
void	set_up_terminal(int flag);
void	handle_interrupt(int signum);
void	handle_quit(int signum);
void	handle_interrupt_child(int signum);

#endif