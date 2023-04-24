/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:45:46 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/24 17:04:53 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * This function needs to work with multiple things
 * Eg: If a pipe is hidden in quotes (double quotes -> "" or single -> '')
 * then you need to ignore it, otherwise, you need to count it.
 * Getting the correct number of pipes is the tricky part.
*/
int	get_pipe_count(char *input, char search)
{
	int	i;
	int	count;
	int	flag_double;
	int	flag_single;

	i = 0;
	count = 0;
	flag_double = 0;
	flag_single = 0;
	while (input[i])
	{
		if (flag_single == 0 && flag_double == 0 && input[i] == search)
			count++;
		if (input[i] == '\'' && flag_single == 0)
			flag_single = 1;
		else if (input[i] == '\'' && flag_single == 1)
			flag_single = 0;
		if (input[i] == '\"' && flag_double == 0)
			flag_double = 1;
		else if (input[i] == '\"' && flag_double == 1)
			flag_double = 0;
		i++;
	}
	return (count);
}

/**
 * This function's responsibility is to traverse the array and 
 * store the position of the pipes.
*/
void	get_pipe_positions(char *input, int *pipes, char search)
{
	int	i;
	int	j;
	int	flag_double;
	int	flag_single;

	i = -1;
	j = -1;
	flag_double = 0;
	flag_single = 0;
	while (input[++i])
	{
		if (flag_single == 0 && flag_double == 0 && input[i] == search)
			pipes[++j] = i;
		if (input[i] == '\'' && flag_single == 0)
			flag_single = 1;
		else if (input[i] == '\'' && flag_single == 1)
			flag_single = 0;
		if (input[i] == '\"' && flag_double == 0)
			flag_double = 1;
		else if (input[i] == '\"' && flag_double == 1)
			flag_double = 0;
	}
}

char	**split_commands(char *input, int *position, int count, char **commands)
{
	int	j;
	int	k;

	j = 0;
	k = -1;
	while (++k < (count + 1))
	{
		if (k == (count))
		{
			commands[k] = ft_malloc_checker(1, (ft_strlen(input) - j + 1));
			ft_strlcpy(commands[k], &input[j], (ft_strlen(input) - j + 1));
		}
		else
		{
			commands[k] = ft_malloc_checker(1, (position[k] - j + 1));
			ft_strlcpy(commands[k], &input[j], (position[k] - j + 1));
		}
		j = position[k] + 1;
	}
	commands[k] = NULL;
	return (commands);
}

/**
 * The parser logic is as follows:
 * 1. Find count for pipes (Because there can be traps in the code).
 * 2. Split on pipes. (How to do that? Identify location of all pipes,
 *  store it in array and then run a splitter at these points.)
 * 3. Now that we have each and every command in their individual string,
 * we can run across the loops and replace every variable input with the 
 * value of the variable itself.
 * 4. Once these are all set, they can be sent to the executor. Its 
 * responsibility is to execute the input. LET'S GO!
*/
void	parser(t_shell *shell)
{
	int		pipe_count;
	int		*pipe_positions;

	add_history(shell->input);
	pipe_count = get_pipe_count(shell->input, '|');
	pipe_positions = (int *)malloc(sizeof(int) * pipe_count);
	if (!pipe_positions)
		perror_and_exit("Could not allocate memory for pipe_positions", 1);
	get_pipe_positions(shell->input, pipe_positions, '|');
	shell->splitted_commands = (char **)malloc(sizeof(char *)
			* (pipe_count + 2));
	if (!shell->splitted_commands)
		perror_and_exit("Could not allocate memory for splitted_commands", 1);
	shell->splitted_commands = split_commands(shell->input, pipe_positions,
			pipe_count, shell->splitted_commands);
	free(pipe_positions);
	expander(shell->splitted_commands, shell);
	execute_commands(shell, shell->splitted_commands, pipe_count + 1);
	free(shell->input);
	free_strings(shell->splitted_commands);
}
