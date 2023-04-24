/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:45:12 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/24 16:58:34 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	return_value_check(int is_neg, int num)
{
	if (is_neg)
		return (num * -1);
	else
		return (num);
}

void	process_input(t_shell *shell)
{
	char	*temp;

	if (shell->input != NULL)
	{
		temp = ft_strtrim(shell->input, " \t");
		free(shell->input);
		shell->input = temp;
	}
}

void	set_up_terminal(int flag)
{
	struct termios	new;
	struct termios	old;

	tcgetattr(STDIN_FILENO, &old);
	new = old;
	if (flag)
		new.c_lflag |= ECHOCTL;
	else
		new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
}

char	*get_env(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->envp[++i] != NULL)
	{
		if (ft_strncmp(shell->envp[i], "PATH", 4) == 0)
			return (ft_strdup(shell->envp[i]));
	}
	return (NULL);
}
