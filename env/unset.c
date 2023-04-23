/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 02:31:42 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/23 20:52:04 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_and_replace_vars(t_shell *shell, char **new_env_vars,
	char **strings)
{
	free_strings(strings);
	free_strings(shell->envp);
	shell->envp = new_env_vars;
	env_count_update(shell);
}

void	copy_env_vars_except_marked(t_shell *shell, char **new_env_vars,
	int *index, int count)
{
	int	i;
	int	flag;
	int	j;
	int	k;

	i = -1;
	k = -1;
	while (shell->envp[++i] != NULL)
	{
		j = -1;
		flag = 0;
		while (++j < count)
			if (i == index[j])
				flag = 1;
		if (flag == 0)
		{
			new_env_vars[++k] = (char *)malloc(sizeof(char) * (
						ft_strlen(shell->envp[i]) + 1));
			ft_strlcpy(new_env_vars[k], shell->envp[i],
				ft_strlen(shell->envp[i]) + 1);
		}
	}
	new_env_vars[++k] = NULL;
}

void	mark_indexes_for_not_copying(t_shell *shell, char **strings, int *index)
{
	int	i;
	int	j;
	int	index_counter;

	i = -1;
	index_counter = -1;
	while (shell->envp[++i] != NULL)
	{
		j = -1;
		while (strings[++j] != NULL)
		{
			if (ft_strncmp(strings[j], shell->envp[i],
					ft_strlen(strings[j])) == 0)
			{
				index[++index_counter] = i;
				break ;
			}
		}
	}
}

int	get_count(t_shell *shell, char **strings)
{
	int		definite_count;
	int		i;
	int		j;

	definite_count = 0;
	i = -1;
	while (shell->envp[++i] != NULL)
	{
		j = -1;
		while (strings[++j] != NULL)
		{
			if (ft_strncmp(strings[j], shell->envp[i],
					ft_strlen(strings[j])) == 0)
			definite_count++;
		}
	}
	return (definite_count);
}

/**
 * Get count of how many variables to unset.
 * Run loop to calculate how many variables actually match with list.
 * Get count of new list size.
 * Realloc for new list.
 * Copy into the new list all the variables that are not to be unset.
*/
//if env_var exists then unset $env_var
// => ERR_UNSET unset: `env_var value': not a valid identifier
// Variables with no value and are in shell->envp
// These variables are currently not being unset correctly
// No value means no equal sign.
void	unset_command(t_shell *shell, char *input)
{
	char	**strings;
	char	**new_env_vars;
	int		count;
	int		*index;
	int		i;

	env_count_update(shell);
	strings = ft_split(input, ' ');
	count = get_count(shell, strings);
	index = (int *)malloc(sizeof(int) * count);
	i = -1;
	while (++i < count)
		index[i] = -1;
	mark_indexes_for_not_copying(shell, strings, index);
	i = -1;
	while (++i < count)
	{
		if (index[i] == -1)
			break ;
	}
	count = i;
	new_env_vars = (char **)malloc(sizeof(char *) * (shell->env_y - count + 1));
	copy_env_vars_except_marked(shell, new_env_vars, index, count);
	free(index);
	free_and_replace_vars(shell, new_env_vars, strings);
}
