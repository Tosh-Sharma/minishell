/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:03:55 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/05 19:43:58 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_builtin_command(char *command, t_shell *shell)
{
	shell->return_value = 0;
	execute_builtin(command, shell);
	exit(shell->return_value);
}

void	execute_process(t_shell *shell, char *command)
{
	char	**address;
	char	*exec_path;

	address = ft_split(getenv("PATH"), ':');
	shell->return_value = 0;
	shell->split_com = ft_split(command, ' ');
	if (is_builtin_command(shell) == 1)
		execute_builtin_command(command, shell);
	else
	{
		if (access(shell->split_com[0], X_OK) != -1)
			exec_path = shell->split_com[0];
		else
			exec_path = find_appropriate_path(shell->split_com, address);
		if (exec_path != NULL)
		{
			shell->return_value = execve(exec_path, shell->split_com,
					shell->envp);
		}
		else
		{
			printf("Command: %s not found\n", shell->split_com[0]);
			exit(1);
		}
	}
}
