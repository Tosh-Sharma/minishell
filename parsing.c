/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:45:46 by tsharma           #+#    #+#             */
/*   Updated: 2023/01/26 15:16:09 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pipe_count(char **input)
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
		if (ft_strcmp(input[i], "\"") == 0)
			count++;
		i++;
	}
	return (count);
}

void	parser(t_shell *shell)
{
	char	**input;
	int		pipe_count;

	pipe_count = get_pipe_count(shell->input);
	execute_commands(shell, input, pipe_count);
}
