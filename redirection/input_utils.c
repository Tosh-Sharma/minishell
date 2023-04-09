/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:20:19 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/09 18:41:27 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_list_size(char **input)
{
	int	size;

	size = 0;
	while (input[size])
		++size;
	return (size);
}

int	get_new_list_size(char **input, int old_size, char *in1, char *in2)
{
	int	i;
	int	new_size;

	i = 0;
	new_size = old_size;
	while (input[i])
	{
		if (ft_strcmp(input[i], in1) == 0
			|| ft_strcmp(input[i], in2) == 0)
			new_size -= 2;
		++i;
	}
	return (new_size + 2);
}

void	create_new_string(t_shell *shell, int old_size, int new_size)
{
	int		i;
	int		j;
	char	**res;

	res = (char **)malloc(sizeof(char *) * (new_size + 1));
	i = -1;
	j = -1;
	while (shell->split_com[++i])
	{
		if (ft_strcmp(shell->split_com[i], "<<") == 0
			|| ft_strcmp(shell->split_com[i], "<") == 0)
		{
			free(shell->split_com[i]);
			if (shell->split_com[++i])
				free(shell->split_com[i]);
		}
		else
			res[++j] = shell->split_com[i];
	}
	res[++j] = NULL;
	free(shell->split_com);
	shell->split_com = res;
}
