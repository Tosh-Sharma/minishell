/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:44:57 by tsharma           #+#    #+#             */
/*   Updated: 2023/03/05 23:46:22 by toshsharma       ###   ########.fr       */
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

int	find_command_checker(t_shell *shell)
{
	//printf("hello\n");
	if (!(ft_strcmp(shell->split_com[0], "echo")))
		return (1);
	else if (!(ft_strcmp(shell->split_com[0], "pwd")))
		return (1);
	else if (!(ft_strcmp(shell->split_com[0], "env")))
		return (1);
	else if (!(ft_strcmp(shell->split_com[0], "export")))
		return (1);
	else if (!(ft_strcmp(shell->split_com[0], "unset")))
		return (1);
	else if (!(ft_strcmp(shell->split_com[0], "cd")))
		return (1);
	return (0);
	//printf("fin\n");
}

int get_index(char *command, int i)
{
	int	index;

	while (command[i] && command[i] == ' ')
		i++;
	if (i == (int)ft_strlen(command))
		return (-1);
	//printf("command[%d] :%c\n", i, command[i]);
	index = i;
	return (index);
}

void	find_command(char *command, t_shell *shell)
{
	int	i;

	i = 0;
	//printf("hello\n");
	env_count_update(shell);
	if (!(ft_strcmp(shell->split_com[0], "echo")))
		mini_echo(command, get_index(command, i + 4), shell);
	else if (!(ft_strcmp(shell->split_com[0], "pwd")))
		mini_pwd();
	else if (!(ft_strcmp(shell->split_com[0], "env")))
		env_command(shell);
	else if (!(ft_strcmp(shell->split_com[0], "export")))
		export_command(shell, command);
	else if (!(ft_strcmp(shell->split_com[0], "unset")))
		unset_command(shell, command);
	else if (!(ft_strcmp(shell->split_com[0], "cd")))
		mini_cd(shell);
	//printf("fin\n");
}