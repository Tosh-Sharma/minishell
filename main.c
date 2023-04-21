/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:04:58 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/21 15:11:26 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

void	new_prompt(t_shell *shell)
{
	if (shell->new_line_flag == 0)
	{
		shell->input = readline("$>:");
		shell->new_line_flag = 1;
	}
	else
	{
		shell->input = readline("$>:");
	}
}

void	print_welcome(void)
{
	printf("\n%s--------------------------------------------------\n", CYAN);
	printf("%s¦                                                ¦\n", CYAN);
	printf("%s¦        Welcome Chapri, to T&T Minishell        ¦\n", WHITE);
	printf("%s¦                                                ¦\n", CYAN);
	printf("%s--------------------------------------------------\n\n", CYAN);
}

void	initialize(t_shell *shell)
{
	main_signal_handling();
	new_prompt(shell);
	check_for_incorrect_syntax(shell->input);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_shell.input = NULL;
	g_shell.new_line_flag = 1;
	if (!envp || envp[0] == 0)
		return (0);
	copy_env_variables(&g_shell, envp);
	print_welcome();
	while (1)
	{
		initialize(&g_shell);
		if (g_shell.input && g_shell.input[0])
			parser(&g_shell);
		else if (g_shell.input == NULL)
		{
			ft_putstr_fd("\nexit\n", 1);
			exit(0);
		}
	}
	return (0);
}
