/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:26:45 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/05 19:09:31 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_printer(char *str, t_shell *shell)
{
	int	i;
	int	j;

	i = -1;
	env_count_update(shell);
	while (++i < shell->env_y)
	{
		j = -1;
		ft_putstr_fd(str, 1);
		while (shell->envp[i][++j])
		{
			if (shell->envp[i][j] == '=')
			{
				ft_putchar_fd(shell->envp[i][j], 1);
				ft_putchar_fd('\"', 1);
				while (shell->envp[i][++j])
					ft_putchar_fd(shell->envp[i][j], 1);
				ft_putchar_fd('\"', 1);
			}
			else
				ft_putchar_fd(shell->envp[i][j], 1);
		}
		ft_putchar_fd('\n', 1);
	}
}

int	var_in_input(char *var, char **split_string, int index)
{
	int		i;
	char	*env_var;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	env_var = ft_malloc_checker(1, i + 1);
	i = -1;
	while (var[++i] && var[i] != '=')
		env_var[i] = var[i];
	printf("env_var_in_input :%s\n", env_var);
	while (split_string[++index])
	{
		printf("split_string[%d] :%s\n", index, split_string[index]);
		printf("ft_strncmp = %d\n", ft_strncmp(env_var, split_string[index], ft_strlen(env_var)));
		printf("equal_check = %d\n", equal_checker(split_string[index]));
		if (equal_checker(split_string[index])
			&& ft_strncmp(env_var, split_string[index], ft_strlen(env_var)) == 0)
			return (1);
	}
	printf("RETURN\n");
	return (0);
}

void	export_command(t_shell *shell, char *input)
{
	char	**split_string;
	int		count;
	int		i;

	split_string = ft_split(input, ' ');
	i = 0;
	while (split_string[i] != NULL)
		i++;
	printf("i = %d\n", i);
	if (i == 1)
		env_command(shell, 1);
	else
	{
		i = 1;
		count = 0;
		printf("split_string[%d] :%s\n", i, split_string[i]);
		while (split_string[i] != NULL)
		{
			printf("var_in = %d\n", var_in_input(split_string[i], split_string, i));
			if (!var_in_input(split_string[i], split_string, i))
			{
				if (env_var_exists(split_string[i], shell) == 0)
					count++;
			}
			i++;
		}
		shell->envp = realloc_new_and_copy_old(shell, count); //need to find a way to update shell->envp while the loop is running because 
		// export tosh tosh=sharma needs to produce tosh=sharma in shell->envp
		store_latest_variables(shell, count, split_string);
		printf("count = %d\n", count);
	}
	// if (shell->exp_values)
		// table_free(shell->exp_values);
	// export_values(shell);
}

void	env_command(t_shell *shell, int flag)
{
	int		i;
	char	*str;

	i = -1;
	env_count_update(shell);
	if (flag == 0)
	{
		while (++i < shell->env_y)
		{
			if (equal_checker(shell->envp[i]))
				printf("%s\n", shell->envp[i]);
		}
	}
	else
	{
		str = ft_strdup("declare -x ");
		export_printer(str, shell);
		free(str);
	}
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
