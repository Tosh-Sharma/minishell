/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:44:57 by tsharma           #+#    #+#             */
/*   Updated: 2023/03/02 19:46:31 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * Command is passed as a ft_split on the bases of spaces
 * between all the words.
*/
char	*find_appropriate_path(char **command, char **address)
{
	char	*path;
	char	*path2;
	int		i;
	int		result;

	i = 0;
	while (address[i] != NULL)
	{
		result = -1;
		path2 = ft_strjoin(address[i], "/");
		path = ft_strjoin(path2, command[0]);
		free(path2);
		result = access(path, X_OK);
		if (result != -1)
			return (path);
		free(path);
		i++;
	}
	if (result == -1)
		return (NULL);
	return (path);
}

//TODO: Single command execution (i.e. when there are no pipes)
void	single_command(t_shell *shell, char **splitted_commands, int count)
{
	(void)shell;
	(void)splitted_commands;
	(void)count;
}
