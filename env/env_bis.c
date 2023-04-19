/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bis.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:26:45 by tsharma           #+#    #+#             */
/*   Updated: 2023/02/27 15:26:15 by toshsharma       ###   ########.fr       */
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
	int	i;
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

/*char	*get_envp_value(int index, char *env_var)// t_shell *shell)
{
	int		i;
	int		j;
	char	*env_value;

	if (!index)
		return (ft_strdup("\""));
	i = 0;
	while (env_var[++index])
		i++;
	env_value = ft_malloc_checker(1, i + 3);
	i = -1;
	j = -1;
	while (env_var[++i])
	{
		if (env_var[i] == '=')
		{
			while (env_var[++i])
				env_value[++j] = env_var[i];
		}
	}
	env_value[++j] = '\0';
	printf("env_value :%s\n", env_value);
	printf("j is = %d\n", j);
	return (env_value);
}

void	export_values(t_shell *shell)
{
	int	i;
	int	j;

	i = -1;
	env_count_update(shell);
	shell->exp_values = (char **)malloc(sizeof(char *) * (shell->env_y + 1));
	while (shell->envp[++i])
	{
		j = -1;
		if (!equal_checker(shell->envp[i]))
			shell->exp_values[i] = get_envp_value(0, shell->envp[i]);
		else
		{
			while (shell->envp[i][++j])
			{
				if (shell->envp[i][j] == '=')
					shell->exp_values[i] = get_envp_value(j, shell->envp[i]);
			}
			printf("exp_values[%d] :%s\n", i, shell->exp_values[i]);
		}
	}
}

void	table_free(char **table)
{
	int	i;
	
	i = 0;
	while (table[i])
		free(table[i]);
	free(table);
}
*/

void	else_env_var_exists(char *env_var, t_shell *shell, int i)
{
	printf("shell->envp[%d] :%s\n", i, shell->envp[i]);
	printf("env_var :%s\n", env_var);

	if ((!equal_checker(shell->envp[i]) && equal_checker(env_var))
		|| (equal_checker(shell->envp[i]) && equal_checker(env_var)))
	{
		printf("ici\n");
		free(shell->envp[i]);
		shell->envp[i] = ft_malloc_checker(1, ft_strlen(env_var) + 1);
		shell->envp[i] = env_var;
	}
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
	env_count_update(shell);
	while (i < shell->env_y
		&& join_and_cmp(var_name, shell->envp[i], len) != 0)
		i++;
	if (i == shell->env_y)
		return (0);
	else
	{
		else_env_var_exists(env_var, shell, i);
		return (1);
	}
}
