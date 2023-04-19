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

int	var_in_input(char *var, char **split_string, int index)
{
	int		i;
	char	*env_var;

	i = 0;
	if (!equal_checker(var))
		env_var = ft_strdup(var);
	else
	{
		while (var[i] && var[i] != '=')
			i++;
		env_var = ft_malloc_checker(1, i + 1);
		i = -1;
		while (var[++i] && var[i] != '=')
			env_var[i] = var[i];
	}
	while (split_string[++index])
	{
		if (equal_checker(split_string[index])
			&& ft_strncmp(env_var, split_string[index], ft_strlen(env_var)) == 0)
			return (1);
	}
	return (0);
}

int	get_count_export(t_shell *shell, char **split_string)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (split_string[++i] != NULL)
		{
			if (!var_in_input(split_string[i], split_string, i))
			{
				if (env_var_exists(split_string[i], shell) == 0)
					count++;
			}
		}
	return (count);
}

char	*var_to_add(char *split_string)
{
	char	*var;

	var = ft_malloc_checker(1, ft_strlen(split_string) + 1);
	var = split_string;
	return (var);
}

void	export_command_extra(t_shell *shell, char **split_string, int count, int i)
{
	while (split_string[++i] != NULL)
	{
		if (!var_in_input(split_string[i], split_string, i))
		{
			if (env_var_exists(split_string[i], shell) == 0)
			{
				shell->vars_to_add[count] = var_to_add(split_string[i]);
				count++;
			}
		}
	}
	shell->vars_to_add[count] = NULL;
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
