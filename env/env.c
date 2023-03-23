/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:26:45 by tsharma           #+#    #+#             */
/*   Updated: 2023/02/10 16:33:03 by toshsharma       ###   ########.fr       */
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
	while (i < shell->env_y &&
        join_and_cmp(var_name, shell->envp[i], len) != 0)
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

/**
 * How below code works:
 * 1. Split the input up.
 * 2. Get count of how many variables need to exported.
 * 3. Split the individual variables up to get the variable name and the value.
 * 4. Malloc for new size.
 * 5. Copy old collection to the new collection. Add stuff at the end.
 * 6. Free old stuff pointers.
*/
// TODO: An illegal syntax check inside the export command.
// This is to be done to ensure we don't add bullshit in the env var list.
// One thing we can do is check for presence of spaces (illegal)
// Another thing we can do is check for = sign. That is necessary
// Lowercase and uppercase are accepted. Find more edge cases in this.
// TODO: Checking for duplicates in the input and eliminating these inputs.
// TODO: In case a parameter already exists, we need to ensure that 
// it gets the updated value this time instead of retaining its old value.
void	export_command(t_shell *shell, char *input)
{
	char	**split_string;
	int		count;
	int		i;

	split_string = ft_split(input, ' ');
	i = 1;
	count = 0;
	while (split_string[i] != NULL)
	{
		if (env_var_exists(split_string[i], shell) == 0)
		{
			//printf("exists");
			count++;
		}
		i++;
	}
	i = 0;
	//printf("count = %d\n", count);
	while (split_string[++i])
		//printf("split_str[%d] :%s\n", i, split_string[i]);
	shell->envp = realloc_new_and_copy_old(shell, count);
	store_latest_variables(shell, count, split_string);
}

void	env_command(t_shell *shell)
{
	int	i;

	i = -1;
	while (++i < shell->env_y)
		printf("%s\n", shell->envp[i]);
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
	shell->env_y = i;
}
