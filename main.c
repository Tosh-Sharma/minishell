/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 16:04:58 by tsharma           #+#    #+#             */
/*   Updated: 2023/04/24 12:32:03 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

void	my_exit(int exit_num)
{
	if (g_shell.input != NULL)
		free(g_shell.input);
	if (g_shell.splitted_commands != NULL)
		free_strings(g_shell.splitted_commands);
	if (g_shell.envp != NULL)
		free_strings(g_shell.envp);
	exit(exit_num);
}

void	new_prompt(t_shell *shell)
{
	if (shell->new_line_flag == 0)
	{
		shell->input = readline("$>:");
		shell->new_line_flag = 1;
	}
	else
		shell->input = readline("$>:");
}

void	print_welcome(int argc, char **argv, t_shell *shell)
{
	(void)argc;
	(void)argv;
	printf("\n%s--------------------------------------------------\n", CYAN);
	printf("%s¦                                                ¦\n", CYAN);
	printf("%s¦        Welcome Chapri, to T&T Minishell        ¦\n", WHITE);
	printf("%s¦                                                ¦\n", CYAN);
	printf("%s--------------------------------------------------\n\n", CYAN);
	shell->input = NULL;
	shell->new_line_flag = 1;
	shell->return_value = 0;
}

void	initialize(t_shell *shell)
{
	set_up_terminal(0);
	main_signal_handling();
	shell->splitted_commands = NULL;
	shell->command = NULL;
	new_prompt(shell);
	check_for_incorrect_syntax(shell->input);
}

void	set_up_terminal(int flag)
{
	struct termios	new;
	struct termios	old;

	tcgetattr(STDIN_FILENO, &old);
	new = old;
	if (flag)
		new.c_lflag |= ECHOCTL;
	else
		new.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
}

int	main(int argc, char **argv, char **envp)
{
	if (!envp || envp[0] == 0)
		return (0);
	copy_env_variables(&g_shell, envp);
	print_welcome(argc, argv, &g_shell);
	while (1)
	{
		initialize(&g_shell);
		if (g_shell.input && g_shell.input[0])
			parser(&g_shell);
		else if (g_shell.input == NULL)
		{
			ft_putstr_fd("exit\n", 1);
			my_exit(g_shell.return_value);
		}
	}
	return (0);
}
