/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:54:48 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/22 15:38:46 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pipe_commands(t_shell *shell, char *command)
{
	int	id;
	int	fd[2];

	shell->split_com = ft_split(command, ' ');
	if (pipe(fd) == -1)
		perror_and_exit("Could not create pipe.", 1);
	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == -1)
		perror_and_exit("Could not fork the process.", 1);
	if (id == 0)
	{
		signal(SIGINT, handle_interrupt_child);
		io_redirection(shell, 1, fd[1]);
		close(shell->temp_fd);
		close(fd[0]);
		close(fd[1]);
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

	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == -1)
		perror_and_exit("Could not fork the process.", 1);
	if (id == 0)
	{
		signal(SIGINT, handle_interrupt_child);
		io_redirection(shell, 1, -1);
		close(shell->temp_fd);
		execute_process(shell, command);
	}
	else
	{
		close(shell->temp_fd);
		while (waitpid(-1, NULL, 0) != -1)
			;
		set_up_terminal(1);
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
		{
			shell->split_com = ft_split(splitted_commands[i], ' ');
			set_io_redirection_flags(shell);
			pipe_commands(shell, splitted_commands[i]);
			free_strings(shell->split_com);
		}
		shell->split_com = ft_split(splitted_commands[i], ' ');
		set_io_redirection_flags(shell);
		multipipe_last(shell, splitted_commands[i]);
		free_strings(shell->split_com);
		if (access("input.txt", F_OK) == 0)
			unlink("input.txt");
	}
}
