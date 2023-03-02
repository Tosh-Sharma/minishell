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

int	find_command(char *command, t_shell *shell)
{
	int	i;

	i = 0;

	/*while (command[i] && command[i] == ' ')
		i++;
	//printf("command[%d] :%c\n", i, command[i]);
	if (command[i] && command[i] == 'e' && command[i + 1] == 'c' &&
		command[i + 2] == 'h' && command[i + 3] == 'o' && (command[i + 4] == ' ' || !command[i + 4]))
		mini_echo(command, get_index(command, i + 4), shell);
	if (command[i] && command[i] == 'c' && command[i + 1] == 'd'
		&& command[i + 2] == ' ')
		mini_cd((command), get_index(command, i + 2));
	if (command[i] && command[i] == 'p' && command[i + 1] == 'w'
		&& command[i + 2] == 'd' && (command[i + 3] == ' ' || !command[i + 3]))
		mini_pwd();
	if (command[i] && command[i] == 'e' && command[i + 1] == 'n'
		&& command[i + 2] == 'v' && (command[i + 3] == ' ' || !command[i + 3]))
		env_command(shell);*/
	if (!(ft_strcmp(shell->split_com[0], "echo")))
		mini_echo(command, get_index(command, i + 4), shell);
	else if (!(ft_strcmp(shell->split_com[0], "pwd")))
		mini_pwd();
	else if (!(ft_strcmp(shell->split_com[0], "env")))
		env_command(shell);
	//else if (!(ft_strcmp(shell->split_com[0], "cd")))
		//mini_cd();
	return (0);
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
			shell->split_com = NULL;
			command_spliter(splitted_commands[i], shell);
			com = find_command(splitted_commands[i], shell);
			free(shell->split_com);
		}
		//printf("\n");
	}
}
