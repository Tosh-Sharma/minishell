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
	pwd = getcwd(NULL, size);
	if (flag)
		unset_command(shell, "unset OLDPWD");
	str = ft_strjoin("export OLDPWD=", pwd);
	free(pwd);
	export_command(shell, str);
	free(str);
}

void	change_pwd(t_shell *shell)
{
	char	*pwd;
	char	*str;
	int		size;

	size = 100;
	pwd = getcwd(NULL, size);
	unset_command(shell, "unset PWD");
	str = ft_strjoin("export PWD=", pwd);
	free(pwd);
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
