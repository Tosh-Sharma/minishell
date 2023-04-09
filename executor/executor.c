/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:54:48 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/07 16:19:02 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_commands(t_shell *shell, char *command)
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
		// Can removed these two lines as they are present
		// inside of the IO redirection.
		dup2(fd[1], STDOUT_FILENO);
		dup2(shell->temp_fd, STDIN_FILENO);
		io_redirection(shell, 1, fd[1]);
		close(shell->temp_fd);
		close(fd[0]);
		close(fd[1]);
		shell->split_com = ft_split(command, ' ');
		execute_process(shell, command);
	}
	else
	{
		close(fd[1]);
		close(shell->temp_fd);
		shell->temp_fd = fd[0];
	}
}

void	multipipe_last(t_shell *shell, char *command)
{
	int	id;

	id = fork();
	if (id == -1)
		perror_and_exit("Could not fork the process.", 1);
	if (id == 0)
	{
		// Can remove this line as it is handled inside
		// the IO redirection file.
		dup2(shell->temp_fd, STDIN_FILENO);
		io_redirection(shell, 0, -1);
		close(shell->temp_fd);
		execute_process(shell, command);
	}
	else
	{
		close(shell->temp_fd);
		while (waitpid(-1, NULL, 0) != -1)
			;
	}
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
			pipe_commands(shell, splitted_commands[i]);
		multipipe_last(shell, splitted_commands[i]);
	}
}
