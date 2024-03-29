/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:44:30 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/18 17:49:14 by toshsharma       ###   ########.fr       */
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

void	expander(char **commands, t_shell *shell)
{
	int	i;
	int	count;
	int	*positions;

	i = -1;
	while (commands[++i] != NULL)
	{
		count = get_env_variable_count(commands[i]);
		if (count > 0)
		{
			positions = (int *)malloc(sizeof(int) * (count));
			if (!positions)
				perror_and_exit("Could not allocate memory for array.", 1);
			store_positions(commands[i], positions);
			commands[i] = replace_env_variable(commands[i], positions, count,
					shell);
			free(positions);
		}
	}
}
