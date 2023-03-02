/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:54:48 by toshsharma        #+#    #+#             */
/*   Updated: 2023/03/02 21:02:25 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * If there is IO redirection needed to be done, it should be done here.
 * Redirection for pipes will also be part of this function.
*/
void	io_n_pipe_redirctin(t_shell *shell, char *command, int i, int count)
{
}

/**
 * Except for the two pipe FDs that are going to be used, we can close all
 * other pipes.
*/
void	close_all_useless_pipes(t_shell *shell, char *command, int i, int count)
{
}

void	execute_process(t_shell *shell, char *command)
{
	char	**command_splitted;
	char	**address;
	char	*exec_path;

	command_splitted = ft_split(command, ' ');
	address = ft_split(getenv("PATH"), ':');
	if (access(command_splitted[0], X_OK) != -1)
		exec_path = command_splitted[0];
	else
		exec_path = find_appropriate_path(command_splitted, address);
	if (exec_path == NULL)
		check_if_builtin(command_splitted, address, exec_path);
	else
	{
		shell->return_value = execve(exec_path, command_splitted, shell->envp);
		perror("Could not execute command.\n");
	}
}

/**
 * How we intend to tackle this part.
 * 1. If there is input to be redirected, do so.
 * 2. If there is output to be redirected, do so.
 * 3. Close unused file descriptors.
 * 4. Fork.
 * 5. In main process, do nothing but wait and close the remaining FDs.
 * 6. In child process,
 * 		a. Is it a built-in command or our command?
 *  	b. If it is a built-in command,
 *			i.		Retrieve the address of the executable path
 *			ii.		Get variables in place for execve.
 *			iii. 	Handle for return value from execve success/failure.
 *		c. If it is our command,
 *			i. 		Execute function as necessary.
 *			ii. 	Handle for return value from command
 * 7. Free everything that needs to be freed.
 * 8. If finished, (　-_･) ︻デ═一 ▸▸▸ 
 * 9. else (ง'̀-'́)ง
*/
void	pipe_command(t_shell *shell, char *command, int i, int count)
{
	int		id;
	char	**address;

	io_n_pipe_redirctin(shell, command, i, count);
	close_all_useless_pipes(shell, command, i, count);
	id = fork();
	if (fork == -1)
		perror_and_exit("Could not fork the process.", 1);
	if (id == 0)
		execute_process(shell, command);
	else
	{
		// TODO: Close the two remaining FDs, that's it.
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
	if (count == 0)
		single_command(shell, splitted_commands, count);
	else
	{
		shell->file = (int **)malloc(sizeof(int *) * count);
		while (++i < count)
		{
			shell->file[i] = (int *)malloc(sizeof(int) * 2);
			if (!shell->file[i])
				perror_and_exit("Could not malloc", 1);
		}
		i = -1;
		while (++i)
			if (pipe(shell->file[i]) == -1)
				perror_and_exit("Could not initialize pipe for FD.", 1);
		while (splitted_commands[++i] != NULL)
			pipe_command(shell, splitted_commands[i], i, count);
	}
}
