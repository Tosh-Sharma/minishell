/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:26:45 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/18 20:40:29 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	equal_checker(char *envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (envp[i] == '=' && envp[i + 1])
			return (1);
		else if (envp[i] == '=' && !envp[i + 1])
			return (1);
	}
	return (0);
}

int	is_env_var(char *str, t_shell *shell)
{
	int		i;
	int		len;
	char	*var_name;

	len = 0;
	while (str[len] && str[len] != '=')
		++len;
	var_name = ft_malloc_checker(1, len + 1);
	ft_strlcpy(var_name, str, len + 1);
	i = 0;
	while (i < shell->env_y)
	{
		if (ft_strncmp(var_name, shell->envp[i], len) != 0)
			++i;
		else
			break ;
	}
	free(var_name);
	if (i == shell->env_y)
		return (0);
	else
		return (1);
}

char	**realloc_new_and_copy_old(t_shell *shell, int count)
{
	char	**new_envs;
	int		i;

	i = -1;
	new_envs = (char **)malloc(sizeof(char *) * (shell->env_y + count + 1));
	while (++i < shell->env_y)
	{
		new_envs[i] = (char *)malloc(sizeof(char) * (ft_strlen(shell->envp[i])
					+ 1));
		ft_strlcpy(new_envs[i], shell->envp[i],
			ft_strlen(shell->envp[i]) + 1);
		free(shell->envp[i]);
	}
	new_envs[i] = NULL;
	free(shell->envp);
	return (new_envs);
}

void	add_env_var(char *str, t_shell *shell)
{
	int	len;

	shell->envp = realloc_new_and_copy_old(shell, 1);
	env_count_update(shell);
	len = ft_strlen(str) + 1;
	shell->envp[shell->env_y] = (char *)malloc(sizeof(char) * len);
	ft_strlcpy(shell->envp[shell->env_y], str, len);
	shell->envp[shell->env_y + 1] = NULL;
	shell->env_y = shell->env_y + 1;
}

void	update_env_var(char *str, t_shell *shell)
{
	int		i;
	int		len;
	char	*var_name;

	i = -1;
	len = 0;
	while (str[len] && str[len] != '=')
		++len;
	var_name = ft_malloc_checker(1, len + 1);
	ft_strlcpy(var_name, str, len + 1);
	while (shell->envp[++i] != NULL)
	{
		if (ft_strncmp(var_name, shell->envp[i], len) == 0)
		{
			free(shell->envp[i]);
			shell->envp[i] = ft_malloc_checker(1, ft_strlen(str) + 1);
			ft_strlcpy(shell->envp[i], str, ft_strlen(str) + 1);
			break ;
		}
	}
	free(var_name);
}
