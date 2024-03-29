/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 23:32:08 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/04 12:28:46 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_var(char *command, int nb, char *var, int len)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	if (nb != 0)
		j = nb;
	while (k < len)
	{
		if (command[j + 1] && (command[j + 1] == '{' || command[j + 1] == '\''
				|| command[j + 1] == '}' || command[j + 1] == ' '
				|| command[j + 1] == '='))
			j++;
		else
		{
			var[k] = command[j + 1];
			j++;
			k++;
		}
	}
	var[k] = '\0';
	return (var);
}

char	*replace_var(char *new_var, char *var, char *env_row, int return_value)
{
	int		i;
	char	*retv_var;

	if (!(ft_strcmp(var, "\?")))
	{
		retv_var = ft_itoa(return_value);
		return (retv_var);
	}
	else
	{
		i = ft_strlen(var) + 1;
		new_var = (char *)malloc(sizeof(char) * ((ft_strlen(env_row)) + 1 - i));
		ft_strlcpy(new_var, &env_row[i], ft_strlen(env_row) + 1 - i);
		return (new_var);
	}
}

char	*dummy_replace_var(char *var, char *pwd, char *oldpwd)
{
	if (ft_strcmp(var, "PWD") == 0 && pwd != NULL
		&& ft_strcmp(pwd, "\""))
		return (ft_strdup(pwd));
	else if (ft_strcmp(var, "OLDPWD") == 0 && oldpwd != NULL
		&& ft_strcmp(oldpwd, "\""))
		return (ft_strdup(oldpwd));
	else
		return (ft_strdup("\""));
}
