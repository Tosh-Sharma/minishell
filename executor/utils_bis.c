/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 13:44:57 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/24 15:55:42 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	ft_putstr_fd("exit\n", 2);
	if (!(ft_isnumber(shell->split_com[1]))
		|| ((ft_atoill(shell->split_com[1], shell)) > 9223372036854775807
			&& (ft_atoill(shell->split_com[1], shell)) < -9223372036854775807
			&& (ft_atoill(shell->split_com[1], shell)) != 9223372036854775807
			&& (ft_atoill(shell->split_com[1], shell))
			!= (-9223372036854775807 - 1)))
	{
		shell->return_value = 255;
		exit_num_arg(shell);
	}
	else
	{
		num = ft_atoill(shell->split_com[1], shell);
		shell->return_value = num % 256;
	}
	my_exit(shell->return_value);
}

void	exit_multiple(t_shell *shell, int i)
{
	if (i > 2 && !(ft_isnumber(shell->split_com[1])))
	{
		shell->return_value = 255;
		ft_putstr_fd("exit\n", 2);
		exit_num_arg(shell);
		my_exit(shell->return_value);
	}
	else
	{
		shell->return_value = 1;
		ft_putstr_fd("exit\n", 2);
		printf("bash: exit: too many arguments\n");
	}
}
