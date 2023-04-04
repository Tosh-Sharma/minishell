/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:55:38 by tsharma           #+#    #+#             */
/*   Updated: 2023/03/29 16:50:32 by toshsharma       ###   ########.fr       */
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
//# include <linux/limits.h>

# define CYAN "\001\033[1;36m\002"
# define WHITE "\001\033[0m\002"
# define GREEN "\001\033[1;32m\002"

// TODO: Return_value is in place for $? handling. Check its requirement
typedef struct s_shell
{
	char	*input;
	char	**envp;
	int		env_count;
	int		return_value;
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
void	env_command(t_shell *shell);
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
void	single_command(t_shell *shell, char **splitted_commands, int count);
void	find_command(char *command, t_shell *shell);
int		find_command_checker(t_shell *shell);
int		get_index(char *command, int i);

#endif