/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:04:58 by tsharma           #+#    #+#             */
/*   Updated: 2023/01/23 12:13:38 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_welcome(void)
{
	printf("\n%s--------------------------------------------------\n", CYAN);
	printf("%s¦                                                ¦\n", CYAN);
	printf("%s¦        Welcome Chapri, to T&T Minishell        ¦\n", WHITE);
	printf("%s¦                                                ¦\n", CYAN);
	printf("%s--------------------------------------------------\n\n", CYAN);
}

// Update history if its not a signal input
// If it is signal input, handle accordingly, else manage as follows
// Allow execution of singlular inputs.
// Allow execution of piped inputs.
// Determine how to allow handle file inputs/ redirects.
void	parse_and_execute(char *input)
{
	if (input[0])
		add_history(input);
	if (is_a_signal(input) == 0)
		execute_it(input);
	else
		execute_signal(input);
}

int	main(void)
{
	t_shell	shell;

	shell.input = NULL;
	shell.sig = 0;
	print_welcome();
	while (1)
	{
		shell.input = readline("$>:");
		parse_and_execute(shell.input);
	}
	return (0);
}
