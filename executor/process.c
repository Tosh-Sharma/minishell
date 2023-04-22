/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:03:55 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/22 17:50:30 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern t_shell	g_shell;

void	execute_builtin_command(t_shell *shell)
{
	shell->return_value = 0;
	execute_builtin(shell->command, shell);
	exit(shell->return_value);
}

void	command_not_found(char *str, int flag)
{
	ft_putstr_fd("Command: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" not found.\n", 2);
	if (flag == 1)
		exit(1);
}

void	execute_process(t_shell *shell)
{
	char	**address;
	char	*exec_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, handle_quit);
	address = ft_split(getenv("PATH"), ':');
	shell->return_value = 0;
	if (is_builtin_command(shell) == 1)
		execute_builtin_command(shell);
	else
	{
		if (access(shell->split_com[0], X_OK) != -1)
			exec_path = shell->split_com[0];
		else
			exec_path = find_appropriate_path(shell->split_com, address);
		if (exec_path != NULL)
		{
			shell->return_value = execve(exec_path, shell->split_com,
					shell->envp);
		}
		else
			command_not_found(shell->split_com[0], 1);
	}
}
