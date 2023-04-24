/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_io_redirection_flags.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:01:29 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/24 17:56:36 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_for_equality(char *input, t_shell *shell)
{
	if (ft_strcmp(input, "<<") == 0)
		shell->is_heredoc_active = 1;
	if (ft_strcmp(input, "<") == 0)
		shell->in_rd = 1;
	if (ft_strcmp(input, ">>") == 0
		|| ft_strcmp(input, ">") == 0)
		shell->op_rd = 1;
}

int	do_we_have_flags(char *word, t_shell *shell)
{
	int	i;

	i = -1;
	while (word[++i])
	{
		if (word[i] == '\'' && shell->fs == 0)
			shell->fs = 1;
		else if (word[i] == '\'' && shell->fs == 1)
			shell->fs = 0;
		if (word[i] == '\"' && shell->fd == 0)
			shell->fd = 1;
		else if (word[i] == '\"' && shell->fd == 1)
			shell->fd = 0;
	}
	if (shell->fs == 1 || shell->fd == 1)
		return (1);
	else
		return (0);
}

void	set_io_redirection_flags(t_shell *shell, char **input)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	shell->fd = 0;
	shell->fs = 0;
	shell->is_heredoc_active = 0;
	shell->in_rd = 0;
	shell->op_rd = 0;
	while (input[++i])
	{
		if (do_we_have_flags(input[i], shell) == 0)
			check_for_equality(input[i], shell);
	}
}
