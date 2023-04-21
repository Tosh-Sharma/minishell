/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:44:57 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/04 12:28:24 by toshsharma       ###   ########.fr       */
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
	if (i == (int)ft_strlen(num))
		return (1);
	return (0);
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
	long long	num;

	if (!(ft_isnumber(shell->split_com[1]))
		|| ((ft_superatoi(shell->split_com[1])) > 9223372036854775806
			&& (ft_superatoi(shell->split_com[1])) < -9223372036854775807
			&& (ft_superatoi(shell->split_com[1])) != 9223372036854775807
			&& (ft_superatoi(shell->split_com[1]))
			!= (-9223372036854775807 - 1)))
		shell->return_value = 255;
	else
	{	
		num = ft_superatoi(shell->split_com[1]);
		shell->return_value = num % 256;
	}
	my_exit(shell->return_value);
}

void	exit_multiple(t_shell *shell, int i)
{
	if (i > 2 && !(ft_isnumber(shell->split_com[1])))
	{
		shell->return_value = 255;
		printf("bash: exit: %s: numeric argument required\n",
			shell->split_com[1]);
		my_exit(shell->return_value);
	}
	else
	{
		shell->return_value = 1;
		printf("bash: exit: too many arguments\n");
	}
}
