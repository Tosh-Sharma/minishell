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

void	swap_strings(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_strings_by_ascii(char **strings, int num_strings)
{
	int	i;
	int	j;

	i = 0;
	while (i < num_strings - 1)
	{
		j = i + 1;
		while (j < num_strings)
		{
			if (ft_strcmp(strings[i], strings[j]) > 0)
				swap_strings(&strings[i], &strings[j]);
			j++;
		}
		i++;
	}
}

void	export_printer(char *str, t_shell *shell)
{
	int	i;
	int	j;

	i = -1;
	sort_strings_by_ascii(shell->envp, shell->env_y);
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

char	*return_shell_level(char *input)
{
	char	*str;
	char	*temp_level;

	temp_level = ft_itoa(ft_atoi(input + 6) + 1);
	str = ft_strjoin("SHLVL=", temp_level);
	free(temp_level);
	return (str);
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
		if (ft_strncmp(envp[i], "SHLVL", 5) == 0)
			shell->envp[i] = return_shell_level(envp[i]);
		else
		{
			shell->envp[i] = ft_malloc_checker(1, (length + 1));
			ft_strlcpy(shell->envp[i], envp[i], length + 1);
		}
		i++;
	}
	shell->envp[i] = NULL;
	shell->env_y = i;
}
