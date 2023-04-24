/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:26:45 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/04 12:31:00 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mini_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 1000);
	if (pwd)
	{
		ft_putstr_fd(pwd, 1);
		ft_putchar_fd('\n', 1);
	}
	free(pwd);
}

void	mini_echo_loop(char *command, int i)
{
	while (command[i])
	{
		while (command[i] && command[i] != '"')
		{
			if ((command[i] == ' ' && command[i + 1] == ' '))
				i++;
			else if (command[i] == '\'')
				while (command[++i] && command[i] != '\'')
					ft_putchar_fd(command[i], 2);
			else
				ft_putchar_fd(command[i++], 2);
		}
		if (command[i] == '"')
			while (command[++i] && command[i] != '"')
				ft_putchar_fd(command[i], 2);
		if (command[i] && command[i + 1])
			i++;
	}
}

void	mini_echo(char *command, int index, t_shell *shell)
{
	if (index < 0)
		write(1, "\n", 1);
	else
		mini_echo_break(command, index, shell);
}

void	mini_cd(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->split_com[1] == NULL)
	{
		while (i < shell->env_y
			&& join_and_cmp("HOME", shell->envp[i], 4) != 0)
			i++;
		if (i == shell->env_y)
			ft_putstr_fd("HOME not set\n", 2);
		else
			get_back_home(shell);
	}
	else
		real_mini_cd(shell);
}
