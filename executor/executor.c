/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:54:48 by toshsharma        #+#    #+#             */
/*   Updated: 2023/02/10 16:36:39 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * The execute_commands section gets the output of the parser.
 * This means the output is already parsed and expanded and is ready to 
 * be executed.
 * Currently, we will only be allowing execution of dummy functions in this
 * function. Namely env, export and unset.
*/
// TODO: Delete this later. ONLY FOR TESTING.

int get_index(char *command, int i)
{
	int	index;

	while (command[i] && command[i] == ' ')
		i++;
	if (i == ft_strlen(command))
		return (-1);
	//printf("command[%d] :%c\n", i, command[i]);
	index = i;
	return (index);
}

void	find_command(char *command, t_shell *shell)
{
	int	i;
	int	flag;

	i = 0;
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
	{
		//if (!(flag = unset_checker(shell)))
			unset_command(shell, command);
	}
	else if (!(ft_strcmp(shell->split_com[0], "cd")))
		mini_cd(command, shell);
}

void	command_spliter(char *command, t_shell *shell)
{
	int	i;

	i = -1;
	shell->split_com = ft_split(command, ' ');
	while (shell->split_com[++i])
		printf("split_com[%d] :%s\n", i, shell->split_com[i]);
}

void	execute_commands(t_shell *shell, char **splitted_commands)
{
	int	i;
	int	com;

	i = -1;
	while (splitted_commands[++i])
	{
		if (splitted_commands[i])
		{
			printf("HELL\n");
			shell->split_com = NULL;
			command_spliter(splitted_commands[i], shell);
			find_command(splitted_commands[i], shell);
			free(shell->split_com);
		}
		//printf("\n");
	}
}
