/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:54:48 by toshsharma        #+#    #+#             */
/*   Updated: 2023/03/03 22:04:30 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * If there is IO redirection needed to be done, it should be done here.
 * Redirection for pipes will also be part of this function.
*/
void	io_n_pipe_redirctin(t_shell *shell, char *command, int i, int count)
{
	// if (pipe(shell->file) != -1)
	// 	perror_and_exit("Could not initialize pipe", 0);
}

void	execute_process(t_shell *shell, char *command)
{
	char	**address;
	char	**command_splitted;
	char	*exec_path;

	address = ft_split(getenv("PATH"), ':');
	if (access(command_splitted[0], X_OK) != -1)
		exec_path = command_splitted[0];
	else
		exec_path = find_appropriate_path(command_splitted, address);
	if (exec_path == NULL)
		check_if_builtin(command_splitted[0], command);
	else
	{
		shell->return_value = 21474836;
		shell->return_value = execve(exec_path, command_splitted, shell->envp);
		perror("Could not execute command.\n");
	}
}

/**
 * UPDATE: The stuff for file redirection happens in this part.
 * In the latter part, we have the execution of custom/built-in functions.
*/
void	pipe_command(t_shell *shell, char *command, int i, int count)
{
	int		id;
	int		fd[2];

	if (pipe(fd) == -1)
		perror_and_exit("Could not create pipe.", 1);
	id = fork();
	//io_n_pipe_redirctin(shell, command, i, count);
	if (id == -1)
		perror_and_exit("Could not fork the process.", 1);
	if (id == 0)
	{
		execute_process(shell, command);
	}
	else
	{
		// Main process.
	}
	waitpid(0, NULL, WNOHANG);
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
	shell->pre_pipe_fd = dup(STDIN_FILENO);
	if (count == 0)
		single_command(shell, splitted_commands, count);
	else
	{
		while (splitted_commands[++i] != NULL)
			pipe_command(shell, splitted_commands[i], i, count);
	}
}
