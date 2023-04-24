/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_pwd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:26:45 by tsharma           #+#    #+#             */
/*   Updated: 2023/02/27 15:26:15 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_previous_pwd(char *pwd, char *pwd_line, int count)
{
	int		i;

	i = -1;
	while (pwd_line[++i])
	{
		if (pwd_line[i] == '=')
		{
			while (pwd_line[++i])
				++count;
		}
	}
	pwd = ft_malloc_checker(1, count + 1);
	i = -1;
	count = -1;
	while (pwd_line[++i])
	{
		if (pwd_line[i] == '=')
		{
			while (pwd_line[++i])
				pwd[++count] = pwd_line[i];
		}
	}
	pwd[++count] = '\0';
	return (pwd);
}

void	real_mini_cd(t_shell *shell)
{
	int	new_dir;

	env_count_update(shell);
	pwd_refresh(shell);
	new_dir = chdir(shell->split_com[1]);
	if (!(new_dir))
		change_pwd(shell);
	else
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(shell->split_com[1], 2);
		ft_putstr_fd(": No such directory or not a directory\n", 2);
		shell->return_value = 1;
	}
}

void	mini_echo_break(char *command, int index, t_shell *shell)
{
	int	i;
	int	flag;

	i = index;
	if (!(ft_strcmp(shell->split_com[1], "-n")))
	{
		shell->new_line_flag = 0;
		i += 2;
	}
	else
		i -= 1;
	while (command[i] == ' ')
		++i;
	flag = 0;
	if ((mini_echo_loop_checker(command, i)))
		shell->return_value = 1;
	else
	{
		mini_echo_loop(command, i);
		if (shell->new_line_flag == 1)
			write(1, "\n", 1);
	}
}

int	mini_echo_loop_checker(char *command, int i)
{
	int	s_quote;
	int	d_quote;

	s_quote = 0;
	d_quote = 0;
	while (command[i])
	{
		if (command[i] == '\'')
			s_quote = !s_quote;
		else if (command[i] == '\"')
			d_quote = !d_quote;
		i++;
	}
	return (s_quote || d_quote);
}
