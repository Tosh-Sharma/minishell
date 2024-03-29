/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:13:13 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/24 17:54:44 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_input_redirect(t_shell *shell, int old_count, int is_piped)
{
	int	i;

	i = old_count;
	while (--i >= 0)
	{
		if (ft_strcmp(shell->split_com[i], "<<") == 0
			|| ft_strcmp(shell->split_com[i], "<") == 0)
		{
			if (ft_strcmp(shell->split_com[i], "<<") == 0)
				heredoc(shell->split_com[i + 1], is_piped);
			else if (ft_strcmp(shell->split_com[i], "<") == 0)
				read_from_file(shell->split_com[i + 1]);
		}
	}
}

void	exec_output_redirect(t_shell *shell, int old_count)
{
	int	i;

	i = old_count;
	while (--i >= 0)
	{
		if (ft_strcmp(shell->split_com[i], ">>") == 0
			|| ft_strcmp(shell->split_com[i], ">") == 0)
		{
			if (ft_strcmp(shell->split_com[i], ">>") == 0)
				append_to_file(shell->split_com[i + 1]);
			else if (ft_strcmp(shell->split_com[i], ">") == 0)
				write_to_file(shell->split_com[i + 1]);
		}
	}
}

int	input_redirection(t_shell *shell, int is_piped)
{
	int	input_redirect;
	int	old_size;
	int	new_size;
	int	i;

	input_redirect = 0;
	i = -1;
	if (shell->in_rd == 1 || shell->is_heredoc_active == 1)
		input_redirect = 1;
	if (input_redirect == 1)
	{
		old_size = get_list_size(shell->split_com);
		new_size = get_new_list_size(shell->split_com, old_size, "<<", "<");
		exec_input_redirect(shell, old_size, is_piped);
		create_new_string(shell, new_size - 2, "<<", "<");
	}
	return (input_redirect);
}

int	output_redirection(t_shell *shell)
{
	int	i;
	int	output_routed;
	int	old_size;
	int	new_size;

	i = -1;
	output_routed = 0;
	if (shell->op_rd == 1)
		output_routed = 1;
	if (output_routed == 1)
	{
		old_size = get_list_size(shell->split_com);
		new_size = get_new_list_size(shell->split_com, old_size, ">>", ">");
		exec_output_redirect(shell, old_size);
		create_new_string(shell, new_size - 2, ">>", ">");
	}
	return (output_routed);
}
