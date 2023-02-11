/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshsharma <toshsharma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:04:58 by tsharma           #+#    #+#             */
/*   Updated: 2023/02/06 23:44:28 by toshsharma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	shell;

void	print_welcome(void)
{
	printf("\n%s--------------------------------------------------\n", CYAN);
	printf("%s¦                                                ¦\n", CYAN);
	printf("%s¦        Welcome Chapri, to T&T Minishell        ¦\n", WHITE);
	printf("%s¦                                                ¦\n", CYAN);
	printf("%s--------------------------------------------------\n\n", CYAN);
}

/** TODO: Need to write a syntax checker for illegal syntax. You can refuse 
 * to handle all terrible input BUT make sure you don't crash.
 **/
int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	shell.input = NULL;
	if (!envp || envp[0] == 0)
		return (0);
	copy_env_variables(&shell, envp);
	print_welcome();
	signal_handling();
	while (1)
	{
		shell.input = readline("$>:");
		check_for_incorrect_syntax(shell.input);
		if (shell.input[0])
		{
			add_history(shell.input);
			parser(&shell);
		}
	}
	return (0);
}
