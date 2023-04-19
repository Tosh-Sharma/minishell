/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:26:45 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/18 19:10:09 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_printer(char *str, t_shell *shell)
{
	int	i;
	int	j;

	i = -1;
	while (++i < shell->env_y)
	{
		j = -1;
		ft_putstr_fd(str, 1);
		while (shell->envp[i][++j])
		{
			if (shell->envp[i][j] == '=')
			{
				ft_putchar_fd(shell->envp[i][j], 1);
				ft_putchar_fd('\"', 1);
				while (shell->envp[i][++j])
					ft_putchar_fd(shell->envp[i][j], 1);
				ft_putchar_fd('\"', 1);
				break ;
			}
			else
				ft_putchar_fd(shell->envp[i][j], 1);
		}
		ft_putchar_fd('\n', 1);
	}
}

void	export_command(t_shell *shell, char *input)
{
	int		count;
	int		i;
	char	**split_string;

	split_string = ft_split(input, ' ');
	count = 0;
	while (split_string[count] != NULL)
		++count;
	if (count == 1)
		env_command(shell, 1);
	else
	{
		i = 0;
		while (split_string[++i] != NULL)
		{
			if (is_env_var(split_string[i], shell) == 0)
				add_env_var(split_string[i], shell);
			else if (is_env_var(split_string[i], shell) == 1 
				&& equal_checker(split_string[i]) == 1)
				update_env_var(split_string[i], shell);
		}
	}
	free_strings(split_string);
}

void	env_command(t_shell *shell, int flag)
{
	int		i;

	i = -1;
	env_count_update(shell);
	if (flag == 0)
	{
		while (++i < shell->env_y)
		{
			if (equal_checker(shell->envp[i]))
				printf("%s\n", shell->envp[i]);
		}
	}
	else
		export_printer("declare -x ", shell);
}

void	copy_env_variables(t_shell *shell, char **envp)
{
	int	count;
	int	i;
	int	length;

	count = 0;
	while (envp[count] != NULL)
		++count;
	shell->envp = (char **)malloc(sizeof(char *) * (count + 1));
	shell->env_y = count;
	i = 0;
	while (i < count)
	{
		length = ft_strlen(envp[i]);
		shell->envp[i] = (char *)malloc(sizeof(char) * (length + 1));
		if (ft_strncmp(envp[i], "SHLVL", 5) == 0)
		{
			shell->envp[i] = ft_strjoin("SHLVL=",
					ft_itoa(ft_atoi(envp[i] + 6) + 1));
		}
		else
			ft_strlcpy(shell->envp[i], envp[i], length + 1);
		i++;
	}
	shell->envp[i] = NULL;
	shell->env_y = i;
}
