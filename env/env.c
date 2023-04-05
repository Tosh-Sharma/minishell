/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:26:45 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/05 12:27:54 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			count++;
		i++;
	}
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
