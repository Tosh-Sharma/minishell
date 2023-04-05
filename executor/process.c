/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 16:03:55 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/05 12:55:47 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_process(t_shell *shell)
{
	char	**address;
	char	*exec_path;

	address = ft_split(getenv("PATH"), ':');
	shell->return_value = 0;
	if (access(shell->split_com[0], X_OK) != -1)
		exec_path = shell->split_com[0];
	else
		exec_path = find_appropriate_path(shell->split_com, address);
	if (exec_path != NULL)
	{
		shell->return_value = execve(exec_path, shell->split_com,
				shell->envp);
		perror("Something went wrong in code execution.");
	}
	else
	{
		ft_putstr_fd("Command not found\n", 2);
		shell->return_value = 127;
		exit(shell->return_value);
	}
}
