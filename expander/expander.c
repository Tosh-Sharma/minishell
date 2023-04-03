/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:44:30 by toshsharma        #+#    #+#             */
/*   Updated: 2023/02/01 12:26:38 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_env_variable_count(char *input)
{
	int	i;
	int	count;
	int	f_s;
	int	f_d;

	i = -1;
	count = 0;
	f_s = 0;
	f_d = 0;
	while (input[++i])
	{
		if (((f_s == 0) || (f_d == 1)) && (input[i] == '$'
				&& input[i + 1] && input[i + 1] != ' '))
			count++;
		if (input[i] == '"' && f_d == 0 && f_s == 0)
			f_d = 1;
		else if (input[i] == '"' && f_d == 1 && f_s == 0)
			f_d = 0;
		if (input[i] == '\'' && f_d == 0 && f_s == 0)
			f_s = 1;
		else if (input[i] == '\'' && f_d == 0 && f_s == 1)
			f_s = 0;
	}
	return (count);
}

void	store_positions(char *input, int *positions)
{
	int	i;
	int	j;
	int	f_s;
	int	f_d;

	i = -1;
	j = -1;
	f_s = 0;
	f_d = 0;
	while (input[++i])
	{
		if (((f_s == 0) || (f_d == 1)) && (input[i] == '$'
				&& input[i + 1] && input[i + 1] != ' '))
			positions[++j] = i;
		if (input[i] == '"' && f_d == 0 && f_s == 0)
			f_d = 1;
		else if (input[i] == '"' && f_d == 1 && f_s == 0)
			f_d = 0;
		if (input[i] == '\'' && f_d == 0 && f_s == 0)
			f_s = 1;
		else if (input[i] == '\'' && f_d == 0 && f_s == 1)
			f_s = 0;
	}
}

/**
 * This function is responsible for expanding variables passed
 * and replacing them with their values.
 * Fun fact: If its double quotes, we need to expand the variable.
 * For single quotes, no need to expand the variable.
*/
// FYI: The positions array has one last extra space. It can be NULL.
void	expander(char **commands, t_shell *shell)
{
	int	i;
	int	count;
	int	*positions;

	i = -1;
	while (commands[++i] != NULL)
	{
		positions = NULL;
		count = get_env_variable_count(commands[i]);
		if (count > 0)
		{
			positions = (int *)malloc(sizeof(int) * (count));
			if (!positions)
				perror_and_exit("Could not allocate memory for array.", 1);
			store_positions(commands[i], positions);
			//printf("command :%s\npositions = %d\ncpositions1 = %d\ncount = %d\n", commands[0], positions[0], positions[1], count);
			commands[i] = replace_env_variable(commands[i], positions, count,
					shell);
			free(positions);
		}
	}
	printf("command :%s\n", commands[0]);
}
