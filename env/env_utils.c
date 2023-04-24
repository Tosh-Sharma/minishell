/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:26:45 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/18 19:10:09 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	not_valid_id(char *str)
{
	ft_putstr_fd("bash: export: \'", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
}

int	counter(t_shell *shell, char **split_string)
{
	int		count;

	count = 0;
	while (split_string[count] != NULL)
		++count;
	if (count == 1)
	{
		env_command(shell, 1);
		return (1);
	}
	return (count);
}

void	export_command(t_shell *shell, char *input)
{
	int		count;
	int		i;
	char	**split_string;

	split_string = ft_split(input, ' ');
	count = counter(shell, split_string);
	if (count != 1)
	{
		i = 0;
		while (split_string[++i] != NULL)
		{
			if (!ft_isalpha(split_string[i][0]))
				not_valid_id(split_string[i]);
			if (ft_strcmp(split_string[i], "=") == 0)
				ft_putstr_fd("bash: export: \'=\': not a valid identifier\n", 2);
			if (is_env_var(split_string[i], shell) == 0
				&& ft_isalpha(split_string[i][0]))
				add_env_var(split_string[i], shell);
			else if (is_env_var(split_string[i], shell) == 1
				&& equal_checker(split_string[i]) == 1
				&& ft_isalpha(split_string[i][0]))
				update_env_var(split_string[i], shell);
		}
	}
	free_strings(split_string);
}

void	env_command(t_shell *shell, int flag)
{
	int		i;

	i = -1;
	if (shell->split_com[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(shell->split_com[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		shell->return_value = 127;
	}
	else
	{
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
}
