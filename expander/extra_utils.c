/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 23:32:08 by toshsharma        #+#    #+#             */
/*   Updated: 2023/04/18 19:50:17 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	new_len_com(char *command, char **res_var, int *positions)
{
	int	i;
	int	p;
	int	res;

	p = 0;
	res = 0;
	i = -1;
	while (command[++i])
	{
		if (i == positions[p])
		{
			i++;
			if (res_var[p] && ft_strcmp(res_var[p], "\""))
				res += (int)ft_strlen(res_var[p]);
			p++;
			while (command[i + 1] && command[i + 1] != ' ' && command[i + 1]
				!= '"' && command[i + 1] != '=' && i + 1 != positions[p])
				i++;
		}
		else
			res++;
	}
	return (res + 1);
}

char	*rep_com(char **chars, int *ints, int *positions, char **res_var)
{
	while (chars[0][++ints[0]])
	{
		if (ints[0] == positions[ints[2]])
		{
			++ints[0];
			if (ft_strcmp(res_var[ints[2]], "\"") == 0)
				++ints[2];
			else
			{
				ints[3] = -1;
				while (res_var[ints[2]][++ints[3]])
					chars[1][++ints[1]] = res_var[ints[2]][ints[3]];
				++ints[2];
			}
			while (chars[0][ints[0] + 1] && chars[0][ints[0] + 1] != ' '
				&& chars[0][ints[0] + 1] != '"' && chars[0][ints[0] + 1] != '\''
				&& chars[0][ints[0] + 1] != '='
				&& (ints[0] + 1) != positions[ints[2]])
				++ints[0];
		}
		else
			chars[1][++ints[1]] = chars[0][ints[0]];
	}
	chars[1][++ints[1]] = '\0';
	return (chars[1]);
}

char	*replace_com(char *res_com, char *command,
	char **res_var, int *positions)
{
	int	i;
	int	j;
	int	k;
	int	l;

	i = -1;
	j = -1;
	k = 0;
	l = 0;
	res_com = rep_com((char *[2]){command, res_com},
			(int [4]){i, j, k, l}, positions, res_var);
	free_strings(res_var);
	return (res_com);
}

char	**rep_env_var(char **c, int *i, int *pos, char ***t)
{
	while (++i[0] < i[3])
	{
		if (pos[i[0]] != 0)
			i[1] = pos[i[0]];
		if (c[0][i[1] + 1] == '{')
			i[1]++;
		i[2] = 0;
		while (c[0][i[1] + 1] && c[0][i[1] + 1] != '"' && c[0][i[1] + 1] != ' '
			&& c[0][i[1] + 1] != '$' && c[0][i[1] + 1] != '}' && c[0][i[1] + 1]
			!= '=' && c[0][i[1] + 1] != '\'' && ++i[2])
			++i[1];
		c[1] = (char *)malloc(sizeof(char) * (i[2] + 1));
		c[1] = get_var(c[0], pos[i[0]], c[1], i[2]);
		i[1] = 0;
		while (i[1] < i[4] && join_and_cmp(c[1], t[1][i[1]],
			ft_strlen(c[1])) != 0)
			++i[1];
		if (i[1] == i[4] && (ft_strcmp(c[1], "\?")) != 0)
			t[0][i[0]] = dummy_replace_var(c[1], c[2], c[3]);
		else
			t[0][i[0]] = replace_var(t[0][i[0]], c[1], t[1][i[1]], i[5]);
		free(c[1]);
	}
	t[0][i[0]] = NULL;
	return (t[0]);
}

char	*replace_env_variable(char *command, int *positions,
	int count, t_shell *shell)
{
	char	*var;
	char	**res_var;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	var = NULL;
	k = 0;
	res_var = (char **)malloc(sizeof(char *) * (count + 1));
	if (!res_var)
		perror_and_exit("Could not allocate memory for array.", 1);
	res_var = rep_env_var((char *[4]){command, var, shell->pwd, shell->oldpwd},
			(int [6]){i, j, k, count, shell->env_y, shell->return_value},
			positions, (char **[2]){res_var, shell->envp});
	shell->res_com = ft_malloc_checker(1,
			new_len_com(command, res_var, positions));
	shell->res_com = replace_com(shell->res_com, command, res_var, positions);
	free(command);
	return (shell->res_com);
}
