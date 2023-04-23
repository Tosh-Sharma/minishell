/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io_redirection_flags.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:01:29 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/23 17:50:31 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_io_redirection_flags(t_shell *shell)
{
	int	i;

	i = -1;
	shell->is_heredoc_active = 0;
	shell->in_rd = 0;
	shell->op_rd = 0;
	while (shell->split_com[++i])
	{
		if (ft_strcmp(shell->split_com[i], "<<") == 0)
			shell->is_heredoc_active = 1;
		if (ft_strcmp(shell->split_com[i], "<") == 0)
			shell->in_rd = 1;
		if (ft_strcmp(shell->split_com[i], ">>") == 0
			|| ft_strcmp(shell->split_com[i], ">") == 0)
			shell->op_rd = 1;
	}
}
