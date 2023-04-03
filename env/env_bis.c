/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:26:45 by tsharma           #+#    #+#             */
/*   Updated: 2023/02/27 15:26:15 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	store_latest_variables(t_shell *shell, int count, char **strings)
{
	int	i;
	int	len;

	i = -1;
	while (++i < count)
	{
		len = (ft_strlen(strings[i + 1]) + 1);
		shell->envp[shell->env_y + i] = (char *)malloc(sizeof(char) * len);
		ft_strlcpy(shell->envp[shell->env_y + i], strings[i + 1], len);
		free(strings[i + 1]);
	}
	shell->envp[shell->env_y + i] = NULL;
	free(strings);
	shell->env_y = shell->env_y + i;
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

int	env_var_exists(char *env_var, t_shell *shell)
{
	int		i;
	int		len;
	char	*var_name;

	len = 0;
	while (env_var[len] && env_var[len] != '=')
		len++;
	var_name = ft_malloc_checker(1, len + 1);
	i = -1;
	while (env_var[++i] && env_var[i] != '=')
		var_name[i] = env_var[i];
	var_name[++i] = '\0';
	i = 0;
	while (i < shell->env_y
		&& join_and_cmp(var_name, shell->envp[i], len) != 0)
		i++;
	if (i == shell->env_y)
		return (0);
	else
	{
		free(shell->envp[i]);
		shell->envp[i] = ft_malloc_checker(1, ft_strlen(env_var) + 1);
		shell->envp[i] = env_var;
		return (1);
	}
}
