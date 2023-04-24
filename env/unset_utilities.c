/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 18:46:07 by toshsharma        #+#    #+#             */
/*   Updated: 2023/02/09 18:52:59 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// The only thing to note is that the variables to be compared should
// be put first because that is the one being appended with an '='.
int	join_and_cmp(const char *s1, const char *s2, size_t n)
{
	char	*s1_plus;
	int		result;

	s1_plus = ft_strjoin(s1, "=");
	result = ft_strncmp(s1_plus, s2, n + 1);
	free(s1_plus);
	return (result);
}

void	free_pwds(char **strings, t_shell *shell)
{
	int	i;

	i = -1;
	while (strings[++i])
	{
		if (ft_strcmp(strings[i], "PWD") == 0)
			nullify_string(shell->pwd);
		if (ft_strcmp(strings[i], "OLDPWD") == 0)
			nullify_string(shell->oldpwd);
	}
}
