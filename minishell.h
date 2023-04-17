/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:55:38 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/05 19:33:00 by toshsharma       ###   ########.fr       */
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

// TODO: Return_value is in place for $? handling. Check its requirement
typedef struct s_shell
{
	char	*input;
	char	**envp;
	char	**exp_values;
	// char	**exp;
	int		return_value;
	// int		exp_y;
	int		env_y;
	char	**env_input;
	char	*res_com;
	int		new_line_flag;
	char	**split_com;
	int		file[2];
	int		temp_fd;
}	t_shell;

void	parser(t_shell *shell);
void	signal_handling(void);
void	copy_env_variables(t_shell *shell, char **envp);
void	check_for_incorrect_syntax(char *input);
void	perror_and_exit(char *input, int exit_code);
void	*ft_malloc_checker(int type, int size);
void	execute_commands(t_shell *shell, char **splitted_commands, int count);
void	env_command(t_shell *shell, int flag);
void	export_command(t_shell *shell, char *input);
void	unset_command(t_shell *shell, char *input);
int		unset_checker(t_shell *shell);
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
void	store_latest_variables(t_shell *shell, int count, char **strings);
char	**realloc_new_and_copy_old(t_shell *shell, int count);
int		env_var_exists(char *env_var, t_shell *shell);
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

#endif