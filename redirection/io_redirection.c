/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:13:13 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/11 14:36:24 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_input_redirect(t_shell *shell, int old_count, int is_piped,
	int redirect_fd)
{
	int	i;

	i = old_count;
	while (i >= 0)
	{
		if (ft_strcmp(shell->split_com[i], "<<") == 0
			|| ft_strcmp(shell->split_com[i], "<") == 0)
		{
			if (ft_strcmp(shell->split_com[i], "<<") == 0)
				heredoc(shell, shell->split_com[i + 1]);
			else if (ft_strcmp(shell->split_com[i], "<") == 0)
				read_from_file(shell, shell->split_com[i + 1]);
		}
		--i;
	}
}

int	input_redirection(t_shell *shell, int is_piped, int redirect_fd)
{
	int	input_redirect;
	int	old_size;
	int	new_size;
	int	i;

	input_redirect = 0;
	i = -1;
	while (shell->split_com[++i])
	{
		if (ft_strcmp(shell->split_com[i], "<<") == 0
			|| ft_strcmp(shell->split_com[i], "<") == 0)
			input_redirect = 1;
	}
	if (input_redirect == 1)
	{
		old_size = get_list_size(shell->split_com);
		new_size = get_new_list_size(shell->split_com, old_size, "<<", "<");
		exec_input_redirect(shell, old_size, is_piped, redirect_fd);
		create_new_string(shell, old_size, new_size - 2);
	}
	return (input_redirect);
}

int	output_redirection(t_shell *shell)
{
	int	i;
	int	output_routed;

	i = -1;
	output_routed = 0;
	while (shell->split_com[++i])
	{
		if (ft_strncmp(shell->split_com[i], ">>", 2) == 0)
		{
			append_to_file(shell, shell->split_com[i + 1]);
			output_routed = 1;
		}
		if (ft_strncmp(shell->split_com[i], ">", 1) == 0)
		{
			write_to_file(shell, shell->split_com[i + 1]);
			output_routed = 1;
		}
	}
	return (output_routed);
}

void	io_redirection(t_shell *shell, int is_piped, int redirect_fd)
{
	int	input_routed;
	int	output_routed;

	input_routed = input_redirection(shell, is_piped, redirect_fd);
	// output_routed = output_redirection(shell);
	if (is_piped == 1 && input_routed == 0)
		dup2(shell->temp_fd, STDIN_FILENO);
	if (is_piped == 1 && output_routed == 0 && redirect_fd != -1)
		dup2(redirect_fd, STDOUT_FILENO);
}
