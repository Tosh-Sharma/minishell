/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:44:57 by tsharma           #+#    #+#             */
/*   Updated: 2023/03/05 23:46:22 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	mini_return_value(t_shell *shell)
{
	printf("bash : %d: command not found\n", shell->return_value);
}

int	ft_isnumber(char *num)
{
	int	i;

	i = 0;
	if (num[0] == '+' || num[0] == '-')
		i++;
	while (num[i] && ft_isdigit(num[i]))
		i++;
	printf("isnumber i = %d\n", i);
	printf("isnumber ftstrlen = %d\n", (int)ft_strlen(num));
	if (i == (int)ft_strlen(num))
		return (0);
	return (1);
}

int	get_index(char *command, int i)
{
	int	index;

	while (command[i] && command[i] == ' ')
		i++;
	if (i == (int)ft_strlen(command))
		return (-1);
	index = i;
	return (index);
}

void	exit_one(t_shell *shell)
{
	int	num;

	if (!(ft_isnumber(shell->split_com[1])))
		shell->return_value = 255;
	printf("shell split 1 :%s\n", shell->split_com[1]);
	num = ft_atoi(shell->split_com[1]);
	printf("shell split 1 = %d\n", num);
	if (num >= 0)
		shell->return_value = num % 256;
	else
		shell->return_value = 256 - (num % 256);
}

void	exit_multiple(t_shell *shell, int i)
{
	if (i > 2 && !(ft_isnumber(shell->split_com[1])))
		shell->return_value = 255;
	else
		shell->return_value = 1;
}
