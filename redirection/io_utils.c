/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:20:19 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/24 15:25:40 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_list_size(char **input)
{
	int	size;

	size = 0;
	while (input[size])
		++size;
	return (size);
}

int	get_new_list_size(char **input, int old_size, char *in1, char *in2)
{
	int	i;
	int	new_size;

	i = 0;
	new_size = old_size;
	while (input[i])
	{
		if (ft_strcmp(input[i], in1) == 0
			|| ft_strcmp(input[i], in2) == 0)
			new_size -= 2;
		++i;
	}
	return (new_size + 2);
}

void	create_new_command(t_shell *shell)
{
	int		i;
	char	*res;
	char	*temp;

	i = -1;
	res = NULL;
	nullify_string(shell->command);
	while (shell->split_com[++i] != NULL)
	{
		temp = res;
		res = ft_strjoin(temp, shell->split_com[i]);
		free(temp);
		if (shell->split_com[i + 1] != NULL)
		{
			temp = res;
			res = ft_strjoin(temp, " ");
			free(temp);
		}
	}
	shell->command = res;
}

void	create_new_string(t_shell *shell, int new_size, char *in1, char *in2)
{
	int		i;
	int		j;
	char	**res;

	res = (char **)malloc(sizeof(char *) * (new_size + 1));
	i = -1;
	j = -1;
	while (shell->split_com[++i])
	{
		if (ft_strcmp(shell->split_com[i], in1) == 0
			|| ft_strcmp(shell->split_com[i], in2) == 0)
		{
			free(shell->split_com[i]);
			if (shell->split_com[++i])
				free(shell->split_com[i]);
		}
		else
			res[++j] = shell->split_com[i];
	}
	res[++j] = NULL;
	free(shell->split_com);
	shell->split_com = res;
	create_new_command(shell);
}

void	io_redirection(t_shell *shell, int is_piped, int redirect_fd)
{
	int	input_routed;
	int	output_routed;

	input_routed = input_redirection(shell, is_piped);
	output_routed = output_redirection(shell);
	if (is_piped == 1 && input_routed == 0)
		dup2(shell->temp_fd, STDIN_FILENO);
	if (is_piped == 1 && output_routed == 0 && redirect_fd != -1)
		dup2(redirect_fd, STDOUT_FILENO);
}
