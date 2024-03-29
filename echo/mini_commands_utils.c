/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_commands_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 12:26:45 by tsharma           #+#    #+#             */
/*   Updated: 2023/02/27 15:26:15 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_count_update(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
			i++;
	shell->env_y = i;
}

void	create_oldpwd(t_shell *shell)
{
	char	*pwd;
	char	*str;
	int		size;
	int		i;

	size = 100;
	pwd = NULL;
	unset_command(shell, "unset OLDPWD");
	i = 0;
	while (i < shell->env_y
		&& join_and_cmp("PWD", shell->envp[i], 3) != 0)
		i++;
	if (i == shell->env_y)
		str = ft_strjoin("export OLDPWD=", shell->pwd);
	else
	{
		pwd = get_previous_pwd(pwd, shell->envp[i], -1);
		str = ft_strjoin("export OLDPWD=", pwd);
		free(pwd);
	}
	export_command(shell, str);
	free(str);
}

void	change_pwd(t_shell *shell)
{
	char	*pwd;
	char	*str;
	int		i;

	pwd = getcwd(NULL, 1000);
	i = 0;
	while (i < shell->env_y
		&& join_and_cmp("PWD", shell->envp[i], 3) != 0)
		i++;
	if (i == shell->env_y)
	{
		nullify_string(shell->pwd);
		shell->pwd = ft_strdup(pwd);
	}
	else
	{
		unset_command(shell, "unset PWD");
		str = ft_strjoin("export PWD=", pwd);
		export_command(shell, str);
		free(str);
	}
	free(pwd);
}

void	pwd_refresh(t_shell *shell)
{
	int		i;

	i = 0;
	while (i < shell->env_y
		&& join_and_cmp("PWD", shell->envp[i], 3) != 0)
		i++;
	if (i == shell->env_y && shell->pwd != NULL)
	{
		nullify_string(shell->pwd);
		shell->pwd = getcwd(NULL, 1000);
	}
	i = 0;
	while (i < shell->env_y
		&& join_and_cmp("OLDPWD", shell->envp[i], 6) != 0)
		i++;
	if (i == shell->env_y)
	{
		nullify_string(shell->oldpwd);
		shell->oldpwd = getcwd(NULL, 1000);
	}
	else
		create_oldpwd(shell);
}

void	get_back_home(t_shell *shell)
{
	char	*res;
	int		*pos;

	pos = (int *)malloc(sizeof(int) * 1);
	pos[0] = 3;
	res = replace_env_variable(ft_strdup("cd $HOME"), pos, 1, shell);
	free_strings(shell->split_com);
	free(pos);
	shell->split_com = ft_split(res, ' ');
	free(res);
	mini_cd(shell);
}
