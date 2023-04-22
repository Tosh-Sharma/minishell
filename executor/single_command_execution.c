/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command_execution.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:29:23 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/22 19:56:12 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_single_process(t_shell *shell, char *exec_path)
{
	int		id;

	id = fork();
	if (id == -1)
		perror_and_exit("Could not fork the process.", 1);
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		io_redirection(shell, 0, -1);
		shell->return_value = 0;
		if (exec_path != NULL)
		{
			shell->return_value = execve(exec_path, shell->split_com,
					shell->envp);
			perror("Something went wrong in code execution.");
		}
	}
	waitpid(-1, NULL, 0);
}

void	clean_up_post_exec(t_shell *shell)
{
	set_up_terminal(1);
	free_strings(shell->split_com);
	if (access("input.txt", F_OK) == 0)
		unlink("input.txt");
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
		execute_builtin(shell->command, shell);
	}
	else
	{
		address = ft_split(getenv("PATH"), ':');
		if (access(shell->split_com[0], X_OK) != -1)
			exec_path = shell->split_com[0];
		else
			exec_path = find_appropriate_path(shell->split_com, address);
		if (exec_path != NULL)
			execute_single_process(shell, exec_path);
		else
			command_not_found(shell->split_com[0], 0);
	}
	clean_up_post_exec(shell);
}
