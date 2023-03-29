/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_thomas.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 22:54:48 by toshsharma        #+#    #+#             */
/*   Updated: 2023/03/29 16:49:05 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 *  FOR THOMAS:
 * The following is the file with all the changes that you made in executor.c
 * However, since we need the multiple pipes code in the executor, I have copied
 * all the code in this file for your refernce.
 * I know some of the code will be copied over from this one to the other
 * executor function
 * - Tosh.
*/
#include "../minishell.h"

/**
 * The execute_commands section gets the output of the parser.
 * This means the output is already parsed and expanded and is ready to 
 * be executed.
 * Currently, we will only be allowing execution of dummy functions in this
 * function. Namely env, export and unset.
*/
// TODO: Delete this later. ONLY FOR TESTING.

/*void	command_spliter(char *command, t_shell *shell)
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
	int	j;

	i = -1;
	while (splitted_commands[++i])
	{
		if (splitted_commands[i])
		{
			//printf("HELL\n");
			shell->split_com = NULL;
			command_spliter(splitted_commands[i], shell);
			find_command(shell);
			j = -1;
			while (shell->split_com[++j])
				free(shell->split_com[j]);
			free(shell->split_com);
			//free(splitted_commands[i]);
		}
		//free(splitted_commands);
		//printf("\n");
	}
}
*/
