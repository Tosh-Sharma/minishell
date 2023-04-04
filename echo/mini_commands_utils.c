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

void	create_oldpwd(t_shell *shell, int flag)
{
	char	*pwd;
	char	*str;
	int		size;

	size = 100;
	pwd = NULL;
	pwd = getcwd(pwd, size);
	if (flag)
	{
		str = ft_strdup("unset OLDPWD");
		unset_command(shell, str);
		free(str);
	}
	str = ft_strdup("export OLDPWD=");
	str = ft_strjoin(str, pwd);
	export_command(shell, str);
	free(str);
}

void	change_pwd(t_shell *shell)
{
	char	*pwd;
	char	*str;
	int		size;

	size = 100;
	pwd = NULL;
	pwd = getcwd(pwd, size);
	str = ft_strdup("unset PWD");
	free(str);
	unset_command(shell, str);
	str = ft_strdup("export PWD=");
	str = ft_strjoin(str, pwd);
	export_command(shell, str);
	free(str);
}

void	pwd_refresh(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->env_y
		&& join_and_cmp("OLDPWD", shell->envp[i], 6) != 0)
		i++;
	if (i == shell->env_y)
		create_oldpwd(shell, 0);
	else
		create_oldpwd(shell, 1);
}

void	get_back_home(t_shell *shell)
{
	char	*str;
	char	*res;
	int		*pos;

	pos = (int *)malloc(sizeof(int) * 1);
	pos[0] = 3;
	str = ft_strdup("cd $HOME");
	res = replace_env_variable(str, pos, 1, shell);
	free(shell->split_com[0]);
	free(shell->split_com);
	shell->split_com = ft_split(res, ' ');
	mini_cd(shell);
}
