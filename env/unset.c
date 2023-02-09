/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 02:31:42 by toshsharma        #+#    #+#             */
/*   Updated: 2023/02/09 19:15:30 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_and_replace_vars(t_shell *shell, char **new_env_vars,
	char **strings, int new_count)
{
	int	i;

	i = -1;
	while (strings[++i] != NULL)
		free(strings[i]);
	free(strings);
	i = -1;
	while (++i < shell->env_count)
		free(shell->envp[i]);
	free(shell->envp);
	shell->envp = new_env_vars;
	i = 0;
	while (shell->envp[i] != NULL)
		i++;
	shell->env_count = i;
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

void	mark_indexes_for_not_copying(t_shell *shell, char **strings, int count,
		int *index)
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
			if (join_and_cmp(strings[j], shell->envp[i],
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
	int		initial_count;
	int		i;
	int		j;

	initial_count = 0;
	while (strings[initial_count] != NULL)
		++initial_count;
	--initial_count;
	definite_count = 0;
	i = -1;
	while (shell->envp[++i] != NULL)
	{
		j = -1;
		while (strings[++j] != NULL)
		{
			if (join_and_cmp(strings[j], shell->envp[i],
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
void	unset_command(t_shell *shell, char *input)
{
	char	**strings;
	char	**new_env_vars;
	int		count;
	int		*index;
	int		i;

	strings = ft_split(input, ' ');
	count = get_count(shell, strings);
	index = (int *)malloc(sizeof(int) * count);
	i = -1;
	while (++i < count)
		index[i] = -1;
	mark_indexes_for_not_copying(shell, strings, count, index);
	i = -1;
	while (++i < count)
	{
		if (index[i] == -1)
			break ;
	}
	count = i;
	new_env_vars = (char **)malloc(sizeof(char *) * (shell->env_count - count));
	copy_env_vars_except_marked(shell, new_env_vars, index, count);
	free_and_replace_vars(shell, new_env_vars, strings, count);
}
