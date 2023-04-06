/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:54:48 by toshsharma        #+#    #+#             */
/*   Updated: 2023/03/29 16:49:09 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * If there is IO redirection needed to be done, it should be done here.
*/
void	io_n_pipe_redirctin(t_shell *shell, char *command, int i, int count)
{
	(void)shell;
	(void)command;
	(void)i;
	(void)count;
}

void	execute_process(t_shell *shell, char *command)
{
	char	**address;
	char	*exec_path;

	address = ft_split(getenv("PATH"), ':');
	//shell->return_value = 0;
	shell->split_com = ft_split(command, ' ');
	if (find_command_checker(shell) == 0)
	{
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
	}
	else
	{
		printf("command in the real find_command :%s\n", command);
		find_command(command, shell);
	}
}

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
		dup2(fd[1], STDOUT_FILENO);
		dup2(shell->temp_fd, STDIN_FILENO);
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

	id = fork();
	if (id == -1)
		perror_and_exit("Could not fork the process.", 1);
	if (id == 0)
	{
		dup2(shell->temp_fd, STDIN_FILENO);
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

/**
 * Here is a pseudocode for the multi pipe implementation.
 * 1. Parse command line arguments to create an array of commands and
 * 	  their arguments.
 * 2. Count the number of pipes in the command and create an array of file
 * 	  descriptors for the pipes.
 * 3. Loop through each command in the pipeline:
 * 	a. Redirect input from previous command's output using dup2().
 * 	b. Redirect output to next command's input using dup2() or set to standard
 * 	   output for the last command.
 * 	c. Close unused file descriptors.
 * 	d. Fork a child process to run the current command using fork().
 * 	e. If this is the child process, run the command using execvp().
 * 	f. If there was an error running the command, print an error message and
 * 	   exit.
 * 	g. If this is the parent process, wait for the child process to finish
 * 	   using waitpid().
 * 	h. Close the input file descriptor if it is not standard input.
 * 	i. Save the output file descriptor for the next command in the pipeline.
 * 4. Close the output file descriptor if it is not standard output.
 * 5. Exit.
*/
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
