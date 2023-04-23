/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_execution.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:29:23 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/18 18:03:35 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_single_process(t_shell *shell, char *exec_path)
{
	int		id;
	int		signal;

	id = fork();
	if (id == -1)
		perror_and_exit("Could not fork the process.", 1);
	if (id == 0)
	{
		io_redirection(shell, 0, -1);
		shell->return_value = 0;
		if (exec_path != NULL)
		{
			shell->return_value = execve(exec_path, shell->split_com,
					shell->envp);
		}
	}
	waitpid(-1, &signal, 0);
	free(exec_path);
	signal_return_value(signal);
}

void	no_command_exec(char *str, t_shell *shell)
{
	shell->return_value = 127;
	ft_putstr_fd("Command: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" not found.\n", 2);
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
	char	**address;
	char	*exec_path;

	shell->split_com = ft_split(splitted_commands[0], ' ');
	set_io_redirection_flags(shell);
	if (is_builtin_command(shell) == 1)
	{
		io_redirection(shell, 0, -1);
		execute_builtin(splitted_commands[0], shell);
	}
	else
	{
		address = ft_split(getenv("PATH"), ':');
		if (access(shell->split_com[0], X_OK) != -1)
			exec_path = ft_strdup(shell->split_com[0]);
		else
			exec_path = find_appropriate_path(shell->split_com, address);
		if (exec_path != NULL)
			execute_single_process(shell, exec_path);
		else
			no_command_exec(shell->split_com[0], shell);
	}
	free_strings(shell->split_com);
	if (access("input.txt", F_OK) == 0)
		unlink("input.txt");
}
