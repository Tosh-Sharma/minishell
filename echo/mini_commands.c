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
	int		size;

	size = 100;
	pwd = NULL;
	pwd = getcwd(pwd, size);
	if (pwd)
	{
		ft_putstr_fd(pwd, 1);
		ft_putchar_fd('\n', 1);
	}
}

void	mini_echo_loop(char *command, int i)
{
	while (command[i])
	{
		while (command[i] && command[i] != '"')
		{
			if ((command[i] == ' ' && command[i + 1] == ' '))
				i++;
			else
			{
				if (command[i] == '\'')
				{
					while (command[++i] && command[i] != '\'')
						ft_putchar_fd(command[i], 1);
				}
				else
					ft_putchar_fd(command[i], 1);
				i++;
			}
		}
		if (command[i] == '"')
		{
			while (command[++i] && command[i] != '"')
				ft_putchar_fd(command[i], 1);
		}
		if (command[i] && command[i + 1])
			i++;
	}
}

int	mini_echo_loop_checker(char *command, int i, int flag)
{
	while (command[i])
	{
		while (command[i] && command[i] != '"')
		{
			// printf("TOP command[%d] :%c\n", i, command[i]);
			if ((command[i] == ' ' && command[i + 1] == ' '))
				i++;
			else
			{
				// printf("MID command[%d] :%c\n", i, command[i]);
				if (command[i] == '\'' && command[i + 1] 
					&& command[i + 1] != '\'')
				{
					// printf("single\n");
					flag = 1;
					while (command[++i])
					{
						// printf("BOT command[%d] :%c\n", i, command[i]);
						if (command[i] == '\'' && flag)
							flag = 0;
						else if (command[i] == '\'' && !flag)
							flag = 1;
					}
					if (flag)
						return (1);
				}
				i++;
			}
		}
		if (command[i] == '"' && command[i + 1] != '"') // TODO: needs to understand when there are no ending " 
		{
			// printf("double\n");
			flag = 2;
			while (command[++i])
			{
				// printf("command[%d] :%c\n", i, command[i]);
				if (command[i] == '"' && flag)
					flag = 0;
				else if (command[i] == '"' && !flag)
					flag = 1;
			}
			if (flag)
				return (1);
		}
		if (command[i] && command[i + 1])
			i++;
	}
	// printf("i = %d\nres = %d\n", i, (int)ft_strlen(command));
	// printf("flag = %d\n", flag);
	return (0);
}

void	mini_echo(char *command, int index, t_shell *shell)
{
	int	i;
	int	flag;

	if (index < 0)
		write(1, "\n", 1);
	else
	{
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
		if ((mini_echo_loop_checker(command, i, flag)))
			printf("not good\n");
		else
		{
			mini_echo_loop(command, i);
			if (shell->new_line_flag == 1)
				write(1, "\n", 1);
		}
	}
}

void	mini_cd(t_shell *shell)
{
	int	new_dir;
	int	i;

	i = 0;
	if (!shell->split_com[1])
	{
		while (i < shell->env_y
			&& join_and_cmp("HOME", shell->envp[i], 4) != 0)
			i++;
		if (i == shell->env_y)
			printf("HOME not set\n"); //error
		else
			get_back_home(shell);
	}
	else
	{
		env_count_update(shell);
		pwd_refresh(shell);
		new_dir = chdir(shell->split_com[1]);
		if (!(new_dir))
			change_pwd(shell);
		else
			printf("cd: %s: No such file or directory\n", shell->split_com[1]); //error
	}
}
