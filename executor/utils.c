/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:44:57 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/24 16:56:00 by tsharma          ###   ########.fr       */
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
	if (address == NULL)
		return (NULL);
	while (address[i] != NULL)
	{
		result = -1;
		path2 = ft_strjoin(address[i], "/");
		path = ft_strjoin(path2, command[0]);
		free(path2);
		result = access(path, X_OK);
		if (result != -1)
			break ;
		free(path);
		i++;
	}
	free_strings(address);
	if (result == -1)
		return (NULL);
	return (path);
}

int	is_builtin_command(t_shell *shell)
{
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
	else if (!(ft_strcmp(shell->split_com[0], "exit")))
		return (1);
	return (0);
}

void	mini_exit(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->split_com[i])
		i++;
	if (i == 1)
	{
		shell->return_value = 0;
		ft_putstr_fd("exit\n", 2);
		my_exit(shell->return_value);
	}
	else if (i == 2)
		exit_one(shell);
	else
		exit_multiple(shell, i);
}

void	execute_builtin(char *command, t_shell *shell)
{
	env_count_update(shell);
	if (!(ft_strcmp(shell->split_com[0], "echo")))
		mini_echo(command, get_index(command, 4), shell);
	else if (!(ft_strcmp(shell->split_com[0], "pwd")))
		mini_pwd();
	else if (!(ft_strcmp(shell->split_com[0], "env")))
		env_command(shell, 0);
	else if (!(ft_strcmp(shell->split_com[0], "export")))
		export_command(shell, command);
	else if (!(ft_strcmp(shell->split_com[0], "unset")))
		unset_command(shell, command);
	else if (!(ft_strcmp(shell->split_com[0], "cd")))
		mini_cd(shell);
	else if (!(ft_strcmp(shell->split_com[0], "exit")))
		mini_exit(shell);
}
