/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:54:48 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/05 14:40:05 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_command(t_shell *shell)
{
	int	id;
	int	fd[2];

	if (pipe(fd) == -1)
		perror_and_exit("Could not create pipe.", 1);
	id = fork();
	if (id == -1)
		perror_and_exit("Could not fork the process.", 1);
	if (id == 0)
	{
		dup2(fd[1], STDOUT_FILENO);
		dup2(shell->temp_fd, STDIN_FILENO);
		close(shell->temp_fd);
		close(fd[0]);
		close(fd[1]);
		execute_process(shell);
	}
	else
	{
		close(fd[1]);
		close(shell->temp_fd);
		shell->temp_fd = fd[0];
	}
}

void	pipe_builtin(t_shell *shell, char *command)
{
	int	fd[2];

	if (pipe(fd) == -1)
		perror_and_exit("Could not create pipe.", 1);
	dup2(fd[1], STDOUT_FILENO);
	dup2(shell->temp_fd, STDIN_FILENO);
	close(shell->temp_fd);
	close(fd[1]);
	execute_builtin(command, shell);
	shell->temp_fd = fd[0];
}

void	multipipe_last(t_shell *shell)
{
	int	id;

	id = fork();
	if (id == -1)
		perror_and_exit("Could not fork the process.", 1);
	if (id == 0)
	{
		dup2(shell->temp_fd, STDIN_FILENO);
		close(shell->temp_fd);
		execute_process(shell);
	}
	else
	{
		close(shell->temp_fd);
		while (waitpid(-1, NULL, 0) != -1)
			;
	}
}

void	last_pipe_command(t_shell *shell, char *command)
{
	shell->split_com = ft_split(command, ' ');
	if (is_builtin_command(shell) != 0)
	{
		close(shell->temp_fd);
		while (waitpid(-1, NULL, 0) != -1)
			;
		execute_builtin(command, shell);
	}
	else
		multipipe_last(shell);
}

void	execute_commands(t_shell *shell, char **splitted_commands, int count)
{
	int		i;

	i = -1;
	shell->temp_fd = dup(STDIN_FILENO);
	if (count == 1)
		single_command_execution(shell, splitted_commands);
	else
	{
		while (++i < (count - 1))
		{
			shell->split_com = ft_split(splitted_commands[i], ' ');
			if (is_builtin_command(shell) != 0)
				pipe_builtin(shell, splitted_commands[i]);
			else
				pipe_command(shell);
		}
		last_pipe_command(shell, splitted_commands[i]);
	}
}
