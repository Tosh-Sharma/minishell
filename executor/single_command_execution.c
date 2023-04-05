/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_execution.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:29:23 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/04 15:55:49 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_single_process(t_shell *shell)
{
	int		id;
	char	**address;
	char	*exec_path;

	id = fork();
	if (id == -1)
		perror_and_exit("Could not fork the process.", 1);
	if (id == 0)
	{
		address = ft_split(getenv("PATH"), ':');
		shell->return_value = 0;
		if (access(shell->split_com[0], X_OK) != -1)
			exec_path = shell->split_com[0];
		else
			exec_path = find_appropriate_path(shell->split_com, address);
		if (exec_path != NULL)
		{
			shell->return_value = execve(exec_path, shell->split_com,
					shell->envp);
			perror("Something went wrong in code execution.");
		}
		else
			perror_and_exit("Command not found", 1);
	}
	waitpid(-1, NULL, 0);
}

/**
 * If it is a single command, first check if it is a built in.
 * If its a built-in, do the needful and then return the result to
 * return_value
 * If its not a built-in, create a fork
 * And in the child process, do the execve stuff and wait for it to be done.
*/
void	single_command_execution(t_shell *shell, char **splitted_commands)
{
	shell->split_com = ft_split(splitted_commands[0], ' ');
	if (is_builtin_command(shell) != 0)
		execute_builtin(splitted_commands[0], shell);
	else
		execute_single_process(shell);
}
