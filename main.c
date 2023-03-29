/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:04:58 by tsharma           #+#    #+#             */
/*   Updated: 2023/02/27 15:35:13 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	shell;

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
		//write(1, "\n", 1);
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

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	shell.input = NULL;
	shell.new_line_flag = 1;
	if (!envp || envp[0] == 0)
		return (0);
	copy_env_variables(&shell, envp);
	print_welcome();
	signal_handling();
	while (1)
	{
		new_prompt(&shell);
		//shell.input = readline("$>:");
		check_for_incorrect_syntax(shell.input);
		if (shell.input[0])
		{
			add_history(shell.input);
			parser(&shell);
		}
	}
	return (0);
}
