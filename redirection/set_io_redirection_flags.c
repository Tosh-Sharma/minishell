/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io_redirection_flags.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:01:29 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/20 17:42:28 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_io_redirection_flags(t_shell *shell)
{
	int	i;

	i = -1;
	shell->is_heredoc_active = 0;
	shell->is_file_input = 0;
	shell->output_write = 0;
	shell->output_append = 0;
	while (shell->split_com[++i])
	{
		if (ft_strcmp(shell->split_com[i], "<<") == 0)
			shell->is_heredoc_active = 1;
		if (ft_strcmp(shell->split_com[i], "<") == 0)
			shell->is_file_input = 1;
		if (ft_strcmp(shell->split_com[i], ">") == 0)
			shell->output_write = 1;
		if (ft_strcmp(shell->split_com[i], ">>") == 0)
			shell->output_append = 1;
	}
}
